
typedef enum ECommandType
{
    eNoOperand,
    eSingleOperand,
    eTwoOperands
}ECommandType;

typedef struct CommandType
{
    const char* command;
    ECommandType type;
}CommandType;
