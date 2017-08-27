#include "Assembler.h"

/*data structures*/
#include "Assembly.h"
#include "Operand.h"
#include "Symbol.h"
#include "Queue.h"

/*libs*/
#include "String.h"
#include "Memory.h"
#include "GeneralMacros.h"
#include "File.h"
#include "Convert.h"
#include "Log.h"

/*handlers*/
#include "CommandHandler.h"
#include "DataHandler.h"
#include "CommandByte.h"
#include "EntryHandler.h"
#include "ExternHandler.h"


#define LABEL_INDICATOR (':')
#define LIGAL_LABEL_CH LETTERS_CH UPPER_CASE_CH NUMBERS_CH

#define COMMENT_CH (';')

/*
    return whether or not the line is a commant
*/
bool Assembly_IsComment(const char* line)
{
    return line ? line[0] == COMMENT_CH : false;
}

/*
    return whether or not the line has a label
*/
bool HasLabel(const char* line)
{
    return String_FindChar(line,LABEL_INDICATOR);
}

/*
    checks if the file specified is a assembly file
*/
bool Assembler_IsAssemblyFile(const char* fileName)
{
	char* ptr = File_FindDot(fileName);

	return !ptr || String_Compare(ptr, ASSEMBLY_END, String_Len(ASSEMBLY_END)) == 0;
}

/*
    return whether or not the line is a code line
*/
bool Assembler_IsCodeLine(char* line)
{
    /* for now will only check that its not a comment*/
    return !String_FindChar(line,';');
}

/*
    Runs on a list of lines and builds the assembly structure passed in context
*/
void Assembler_CreateSymbolsIter(void* data, size_t len, void* context)
{
    Assembly* assembly = context;
    char line[MAX_LINE_LEN];
    char* commandLine = line;
    char* label = NULL;
    Symbol symbol;
    size_t size = 0;
    
    if(!assembly || !data)
    {
        return;
    }
    
    /* copy the line to a buffer to mess around with*/
    Memory_Copy(line, data, len);

    /* clean the line from tabs and stuff*/
    String_SimplfyLine(line);

    /* if the line is not of a use to me ignore it*/
    if(String_Empty(line) || Assembly_IsComment(line))
    {
        return;
    }

    if(HasLabel(line))
    {
        commandLine = String_SplitToTwo(line, LABEL_INDICATOR);
        label = line;
        
        /* position the pointer in the command begining */
        while(*commandLine == SPACE_CH) commandLine++;
    }

    /*check for extern command*/
    if(ExternHandler.IsHandler(commandLine))
    {
        ExternHandler.Add(commandLine,&assembly->prog.data.bytes,&assembly->prog.symbols);
    }
    /*check for entry */
    else if(EntryHandler.IsHandler(commandLine))
    {
        /*add to queue of pennding commands to anlys later*/
        Queue_enqueue(&assembly->penndingCommands, commandLine, String_Len(commandLine) + 1);
    }
    /*check if its a data command*/
    else if(DataHandler.IsHandler(commandLine))
    {
        /*do we have a label?*/
        if(label)
        {
            /*add to symbol list*/
            symbol = Symbol_Init(label,assembly->prog.data.counter,eDataSymbol);
            List_Add(&assembly->prog.symbols, &symbol, sizeof(Symbol));
        }
        /*calculate the size of the command and add it to the command counter*/
        size = DataHandler.GetSize(commandLine);
        if(size == 0)
        {
            /*print a warning of a wrong command*/
            Log(eError,"un supported data command: %s",commandLine);
            NotifyError(&assembly->prog);
        }
        else
        {
            /*advence the data counter and add the command to the list of data bytes*/
            assembly->prog.data.counter += size;
            DataHandler.Add(commandLine,&assembly->prog.data.bytes,&assembly->prog.symbols);
        }

    }
    else if(CommandHandler.IsHandler(commandLine))
    {
        /*do we have a label?*/
        if(label)
        {
            /*add to symbol list*/
            symbol = Symbol_Init(label,assembly->prog.code.counter,eCommandSymbol);
            List_Add(&assembly->prog.symbols, &symbol, sizeof(Symbol));    
        }
        /*calculate the size of the command and add it to the command counter*/
        size = CommandHandler.GetSize(commandLine);
        if(size == 0)
        {
            /*print a warning of a wrong command*/
            Log(eError,"un supported command: %s",commandLine);
            NotifyError(&assembly->prog);
        }
        else
        {
            /*  advence the command counter and add the command to the list of 
                pennding commands for later analysis*/
            assembly->prog.code.counter += size;
            Queue_enqueue(&assembly->penndingCommands, commandLine, String_Len(commandLine) + 1);
        }
    }
    else
    {
        Log(eError,"un sopported command in assembly file");
        NotifyError(&assembly->prog);
    }
}

/*
    Runs on list of commands and creates the byte
*/
void Assembler_ParseCommands(void* data, size_t len, void* context)
{
    Programme* prog = context;
    char line[MAX_LINE_LEN];
    char* commandLine = line;
    char* params = NULL;
    
    if(!prog || !data || len == 0)
    {
        return;
    }
    /* copy the line to a buffer to mess oround with*/
    Memory_Copy(line, data, len);
    
    /* clean the line from tabs and stuff*/
    String_SimplfyLine(line);

    /*should always be true*/
    if(EntryHandler.IsHandler(commandLine))
    {
        if(!EntryHandler.Add(commandLine,&prog->code.bytes,&prog->symbols))
        {
            Log(eError,"Failed parsing entry line : %s",commandLine);
            NotifyError(prog);    
        }
    }
    else if(CommandHandler.IsHandler(commandLine))
    {
        if(!CommandHandler.Add(commandLine,&prog->code.bytes,&prog->symbols))
        {
            Log(eError,"Failed adding command line to memory : %s",commandLine);
            NotifyError(prog);    
        }
    }
    else
    {
        Log(eError,"Recieved an unsupported command : %s",commandLine);
        NotifyError(prog);
    }
}

/*
    for each byte in bytes list parse and add to object file
    note : pubCount should be set to the base address of the programme
*/
int pubCount = 0;
void WriteObjectIter(void* data,size_t len,void* context)
{
    char buffer[MAX_LINE_LEN];
    const int* byte = (int*)data;
    int value;
    FILE* file = context;
    
    if(!byte || !file)
    {
        return;
    }
    
    /*clean the buffer*/
    Memory_Set(buffer,0,sizeof(buffer));
    
    /*clean and copy the content of the byte to a variable*/
    Memory_Set(&value,0,sizeof(value));
    Memory_Copy(&value,byte,sizeof(byte));
    
    /* append the address and command to the buffer*/
    Convert_DecimalToBase4Str(pubCount,&buffer[String_Len(buffer)],sizeof(buffer) - String_Len(buffer),4);
    String_Append(buffer,SPACE_STR,sizeof(SPACE_STR));
    Convert_DecimalToBase4Str(value,&buffer[String_Len(buffer)],sizeof(buffer) - String_Len(buffer),5);
    
    /*write the line to a file*/
    if(!File_WriteLine(file,buffer))
    {
        Log(eError,"Failed Writing to file :: %s",buffer);
    }
    
    /* advance counter*/
    pubCount ++;
}

/*
    writes the code and data to the object file
*/
bool WriteObjectFile(char fileName[],List* code,List* data,int baseAddress)
{
    pubCount = baseAddress;

    /*append the data section to the code list*/
    List_AddToList(code,data);
    
    /*run on list and write to file*/
    return File_WriteToFile(fileName,*code,&WriteObjectIter);
}

/*
    Assemble the as file provided and write to output files
*/
bool Assembler_AssembleFile(char* baseFileName)
{
    int baseAddress = 100;
    char fileName[MAX_FILE_NAME];
    Assembly assembly = Assembly_Init();

    /*create assembly file name from base file name*/
    File_CreateName(baseFileName,ASSEMBLY_END,fileName,sizeof(fileName));
    
    /*open the file*/
    FILE* file = File_Open(fileName, "r");
    if(!file)
    {
        Log(eError,"Could not open file");
        return false;
    }

    /*add base address to programme counter*/
    assembly.prog.code.counter = 100;

    /* create symbol table*/
    File_ForEach(file, &Assembler_CreateSymbolsIter,&assembly);

    /*close the file*/
    if(!File_Close(file))
    {
        Log(eError, "Could not close file");
        return false;
    }

    /*update symbol table datas base address*/
    List_ForEach(assembly.prog.symbols,&Symbol_UpdateDataSymbolAddressIter,&assembly.prog.code.counter);
    
    /*create command byte list*/
    Queue_ForEach(assembly.penndingCommands, &Assembler_ParseCommands, &assembly.prog);

    /*create entry file*/
    File_CreateName(baseFileName,ENTRY_END,fileName,sizeof(fileName));
    if(!WriteEntryFile(fileName,&assembly.prog.symbols))
    {
        Log(eError,"Couldnt create entry file :: %s",fileName);
        return false;
    }

    /*create extern file*/
    File_CreateName(baseFileName,EXTERN_END,fileName,sizeof(fileName));
    if(!WriteExternFile(fileName,&assembly.prog.code.bytes,&assembly.prog.symbols,100))
    {
        Log(eError,"Couldnt create extern file :: %s",fileName);
        return false;
    }

    /*create object file*/
    File_CreateName(baseFileName,OBJECT_END,fileName,sizeof(fileName));
    if(!WriteObjectFile(fileName,&assembly.prog.code.bytes,&assembly.prog.data.bytes,100))
    {
        Log(eError,"Couldnt create object file :: %s",fileName);
        return false;
    }

    /*free assembly resources*/
    Assembly_Delete(&assembly);

    return true;
}







