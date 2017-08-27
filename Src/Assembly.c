#include "Assembly.h"
#include "Memory.h"
#include "String.h"


Programme Programme_Init()
{
    Programme prog;
    
    prog.data = Segment_Init();
    prog.code = Segment_Init();
    prog.symbols = List_Init();
    
    return prog;
}

void Programme_Delete(Programme* prog)
{
    Segment_Delete(&prog->data);
    Segment_Delete(&prog->code);
    List_Delete(&prog->symbols,NULL,NULL);
}

Assembly Assembly_Init()
{
    Assembly assembly;

    /*create sybol table*/
    assembly.prog = Programme_Init();
    assembly.penndingCommands = Queue_Init();

    return assembly;
}

void Assembly_Delete(Assembly* as)
{
    Programme_Delete(&as->prog);
    Queue_Delete(&as->penndingCommands,NULL,NULL);
}

