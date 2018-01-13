#include <Arduino.h>
#include <Stream.h>

#define Rx_Buffer 64

// Warning For Each Address Should Over 255
#define InPut_Size 16 // 16x16 = 256 Bit
#define OutPut_Size 16 // 16x16 = 256 Bit
#define Int_Size 32 // Int Data 32 Point 
#define Uint_Size 32 // Uint Data 32 Point
#define Float_Size 32 // Double 32 Point
#define String_Size 32 // String 32 Message
#define Diagnostics_Size 16 // 16x16 = 256 Bit
#define Ascii_Size 16

#define SetOutPut(pin) pinMode(pin,OUTPUT)
#define SetIntPut(pin) pinMode(pin,INPUT)
#define MovWord(Src,Des) Src = Des
#define MovBit(reg,bit,state) (state)? SetBit(reg,bit) : ClearBit(reg,bit)
#define GetBit(reg,bit) (reg>>bit)&0x01
#define SetBit(reg,bit) reg=reg|(1<<bit)
#define ClearBit(reg,bit) reg = reg&(~(1<<bit))
#define MovData(reg1,reg2) reg1 = reg2
#define InRange(Data,Rmin,Rmax) ((Data<=Rmax)&&(Data>Rmin))? true : false 
//#define ClearBit()
enum EXType
{
    InPut = 99,
    OutPut = 100,
    INT = 101,
    UINT = 102,
    FLOAT = 103,
    STRING = 104,
    DIAGNOSTICS = 105
};

enum command
{
    Eof = 3,
    GetTiming = 238,
    GetDev = 239,
    Write_Word = 240,
    Write_Bit = 241,
    Read_Word = 242,
    RequestFromServer = 243,
    DeviceAck = 244,
    Header = ':',
    NewLine = '\n',
    AddressNotSupprt = 245,
    SizeOverFlow = 246,
    CannotWrite = 247,
    ErrorByCommand = 248,
    NormalStatus = 249,
    BitSetOverRange = 250,
    SizeOptimize = 251,
    MonitorProgram = 252,
    ReadProgram = 253,
    WriteProgram = 254,
    StopProgram = 255,
};

class ProtocolEx
{
    public:
        void Begin(byte Station,Stream &Hardware);
        void SetDeviceName(String DevName){ DeviceName = DevName; };
        String GetDevName(){return DeviceName;}
        bool ScanLoop();
    private:

        union ByteConverse
        {
            byte SetByte[sizeof(float)];
            float GetFloat;
            int GetInt;
            unsigned int GetUInt;
            unsigned long Getlong;
        };
        
        ByteConverse TypeConvert;

    public:
        unsigned int I[InPut_Size];
        unsigned int Q[OutPut_Size];
        int Int[Int_Size];
        unsigned int UInt[Uint_Size];
        float Float[Float_Size];
        char Str[String_Size][Ascii_Size];
        unsigned int Diag[Diagnostics_Size];
        void FillText(byte Address,String Message);
    private:
        String DeviceName;
        Stream *Uart ;
        byte Sta ;
        void flush();
        void WriteW(EXType T,int Addr,byte NumberWrite,byte *Data);
        void WriteB(EXType T,int Addr,byte Bitn,bool Data);
        void ReadW(EXType T,int Addr ,byte Number);
        void GetSize();
        void WriteCode(command cmd);
        unsigned long TimingProcess ;
        bool ConnectToPC;
};
