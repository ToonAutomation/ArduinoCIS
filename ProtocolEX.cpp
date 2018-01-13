
#include "ProtocolEx.h"
#include <stdio.h>
#include <stdlib.h>
byte RX[Rx_Buffer];
unsigned char *RXPTR;
void ProtocolEx::Begin(byte Station,Stream &Hardware)
{
    Uart = &Hardware;
    Sta = Station;
}


bool ProtocolEx::ScanLoop()
{ 
    ConnectToPC = false ;
    int BufferIn = Uart->available();
    if(BufferIn <= 0) return false ;
    flush();
    delay(50);
    int CountByte = Uart->available();

    if(CountByte <= 0) return false;

    if(CountByte > 0)
    {
          Uart->readBytes(&RX[0],CountByte);
          Uart->flush();
    }
    /*************************************************/
    
    // Check Node
    if(RX[0] != Header) return false;
    if(RX[1] != Sta) return false ;

    switch(RX[2])
    {
        case RequestFromServer :
            WriteCode(NormalStatus);
            ConnectToPC = true ;
        break;
        case Read_Word :
           // ReadW(EXType T,int Addr ,byte Number);
           ReadW((EXType)RX[3],(RX[4]<<8)|(RX[5]),RX[6]);
           ConnectToPC = true ;
        break;
        case Write_Word:
            WriteW((EXType)RX[3],(RX[4]<<8)|(RX[5]),RX[6],&RX[7]);
            ConnectToPC = true ;
        break;
        case Write_Bit:
            WriteB((EXType)RX[3],(RX[4]<<8)|(RX[5]),RX[6],RX[7]&1);
            ConnectToPC = true ;
        break;
        case SizeOptimize:
            GetSize();
            ConnectToPC = true ;
        case GetDev :
             Uart->write((byte)Header);
             Uart->write((byte)Sta);
             Uart->print(DeviceName);
             ConnectToPC = true ;
        break;
        case GetTiming :
            TypeConvert.Getlong = TimingProcess;
            Uart->write((byte)Header);
            Uart->write((byte)Sta);
            Uart->write(TypeConvert.SetByte[0]);
            Uart->write(TypeConvert.SetByte[1]);
            Uart->write(TypeConvert.SetByte[2]);
            Uart->write(TypeConvert.SetByte[3]);
            ConnectToPC = true ;
        break;
    }

/*************************************************/
     TimingProcess = millis() - TimingProcess;
/*************************************************/
    return ConnectToPC;
}
   
void ProtocolEx::flush()
{
    /*
    byte *P;
    P=&RX[0];
    while(P <= &RX[Rx_Buffer-1])
    {
        *P = 0x00;
         P++;
    }
    */
    memset(&RX[0],'\0',sizeof(Rx_Buffer));
}




void ProtocolEx::WriteW(EXType T,int Addr,byte NumberWrite,byte *Data)
{
        int n = 0;
        switch(T)
        {
                case InPut :
                    WriteCode(AddressNotSupprt);
                    return;
                break;
                case OutPut :
                    if((Addr+NumberWrite) > OutPut_Size) 
                    {
                        WriteCode(SizeOverFlow);
                        return;
                    }

                    while(n <= NumberWrite)
                    {
                         Q[Addr+n] = (*(Data+1)<<8)|(*Data); 
                         Data+=2;
                         n+=1;
                    }
                    WriteCode(NormalStatus);
                    return;
                break;
                case INT :
                    if((Addr+NumberWrite) > Int_Size) 
                    {
                        WriteCode(SizeOverFlow);
                        return;
                    }

                    while(n <= NumberWrite)
                    {
                         Int[Addr+n] = (*(Data+1)<<8)|(*Data); 
                         Data+=2;
                         n+=1;
                    }
                        WriteCode(NormalStatus);
                        return;
                break;
                case UINT :
                    if((Addr+NumberWrite) > Uint_Size) 
                    {
                        WriteCode(SizeOverFlow);
                        return;
                    }

                          while(n <= NumberWrite)
                    {
                         UInt[Addr+n] = (*(Data+1)<<8)|(*Data); 
                         Data+=2;
                         n+=1;
                    }
                    return;
                break;
                case FLOAT :
                    if((Addr+NumberWrite) > Float_Size) 
                    {
                        WriteCode(SizeOverFlow);
                        return;
                    }

                          while(n <= NumberWrite)
                    {
                         TypeConvert.SetByte[0] = *(Data);
                         TypeConvert.SetByte[1] = *(Data+1);
                         TypeConvert.SetByte[2] = *(Data+2);
                         TypeConvert.SetByte[3] = *(Data+3);

                         Float[Addr+n] = TypeConvert.GetFloat;
                         Data+=4;
                         n+=1;
                    }
                        WriteCode(NormalStatus);
                        return;
                break;
                case STRING :
                    if((Addr+NumberWrite) > String_Size) 
                    {
                        WriteCode(SizeOverFlow);
                        return;
                    }


                        while(n <= NumberWrite)
                    {
                         for(int x = 0; x<= Ascii_Size-1;x++)
                         {
                                Str[Addr+n][x] = *Data;
                                Data++;    
                         }
                         n+=1;
                    }
                        WriteCode(NormalStatus);
                        return;
                break;
                case DIAGNOSTICS :
                    
                     if((Addr+NumberWrite) > Diagnostics_Size) 
                    {
                        WriteCode(SizeOverFlow);
                        return;
                    }

                    if((&RX[Rx_Buffer-1] - Data) >= (NumberWrite*1))
                    {
                        WriteCode(ErrorByCommand);
                        return;
                    }

                        while(n <= NumberWrite)
                    {
                        TypeConvert.SetByte[0] = *(Data) ; 
                        TypeConvert.SetByte[1] = *(Data+1);

                         Diag[Addr+n] = TypeConvert.GetUInt;
                         Data+=2;
                         n+=1;
                    }

                    WriteCode(NormalStatus);
                    return;
                break;
                default :        
                    WriteCode(AddressNotSupprt);
        }

}

void ProtocolEx::WriteB(EXType T,int Addr,byte Bitn,bool Data)
{

            if((Bitn < -1)||(Bitn  > 15))
            {
                WriteCode(BitSetOverRange);
                return;
            }

    switch(T)
        {
                case InPut :
                        WriteCode(AddressNotSupprt);
                        return;
                break;
                case OutPut :
                    if( Addr > OutPut_Size) 
                    {
                        WriteCode(SizeOverFlow);
                        return;
                    }

                    MovBit(Q[Addr],Bitn,Data);
                    WriteCode(NormalStatus);
                    return;
                break;
                case INT :
                    if( Addr > Int_Size) 
                    {
                        WriteCode(SizeOverFlow);
                        return;
                    }

                        MovBit(Int[Addr],Bitn,Data);
                        WriteCode(NormalStatus);
                        return;
                break;
                case UINT :
                    if( Addr > Uint_Size) 
                    {
                        WriteCode(SizeOverFlow);
                        return;
                    }
                        MovBit(UInt[Addr],Bitn,Data);
                        WriteCode(NormalStatus);
                        return;
                break;
                case FLOAT :
                        WriteCode(AddressNotSupprt);
                break;
                case STRING :
                        WriteCode(AddressNotSupprt);
                break;
                case DIAGNOSTICS :
                    
                     if((Addr) > Diagnostics_Size) 
                    {
                        WriteCode(SizeOverFlow);
                        return;
                    }

                    MovBit(Diag[Addr],Bitn,Data);

                    WriteCode(NormalStatus);
                    return;
                break;
                default :        
                    WriteCode(AddressNotSupprt);
        }
}

void ProtocolEx::ReadW(EXType T,int Addr ,byte Number)
{
        int n = 0;
        switch(T)
        {
                case InPut :
                    if((Addr+Number) > InPut_Size) 
                    {
                        WriteCode(SizeOverFlow);
                        return;
                    }
                    
                    Uart->write((byte)Header);
                    Uart->write((byte)Sta);
                    Uart->write((byte)InPut);
                    while(n <= Number)
                    {
                        //  TypeConvert.GetInt = *I[Addr+n];
                        Uart->write(((I[Addr+n]>>8)&0xFF));
                        Uart->write((I[Addr+n]&0xFF));
                        n++;
                    }
                                 
                    return;
                break;
                case OutPut :
                    if((Addr+Number) > OutPut_Size) 
                    {
                        WriteCode(SizeOverFlow);
                        return;
                    }

                    Uart->write((byte)Header);
                    Uart->write((byte)Sta);
                    Uart->write((byte)OutPut);
                    while(n <= Number)
                    {
                        Uart->write(((Q[Addr+n]>>8)&0xFF));
                        Uart->write((Q[Addr+n]&0xFF));
                        n++;
                    }
                    
                    return;
                break;
                case INT :
                       if((Addr+Number) > Int_Size) 
                    {
                        WriteCode(SizeOverFlow);
                        return;
                    }

                    
                    Uart->write((byte)Header);
                    Uart->write((byte)Sta);
                    Uart->write((byte)INT);
                    while(n <= Number)
                    {
                     Uart->write((Int[Addr+n]>>8)&0xFF);
                     Uart->write((Int[Addr+n]&0xFF));
                     n++;
                    }
                    
                    return;
                break;
                case UINT :
                      if((Addr+Number) > Uint_Size) 
                    {
                        WriteCode(SizeOverFlow);
                        return;
                    }

                    Uart->write((byte)Header);
                    Uart->write((byte)Sta);
                    Uart->write((byte)UINT);
                    while(n <= Number)
                    {
                        Uart->write(((UInt[Addr+n]>>8)&0xFF));
                        Uart->write((UInt[Addr+n]&0xFF));
                        n++;
                    }
                    
                    return;
                break;
                case FLOAT :
                      if((Addr+Number) > Float_Size) 
                    {
                        WriteCode(SizeOverFlow);
                        return;
                    }

                    Uart->write((byte)Header);
                    Uart->write((byte)Sta);
                    Uart->write((byte)FLOAT);
                    while(n <= Number)
                    {
                        TypeConvert.GetFloat = Float[Addr+n];
                        Uart->write(TypeConvert.SetByte[3]);
                        Uart->write(TypeConvert.SetByte[2]);
                        Uart->write(TypeConvert.SetByte[1]);
                        Uart->write(TypeConvert.SetByte[0]);
                        n++;
                    }                   
                    return;
                break;
                case STRING :
                       if((Addr+Number) > String_Size) 
                    {
                        WriteCode(SizeOverFlow);
                        return;
                    }
                    Uart->write((byte)Header);
                    Uart->write((byte)Sta);
                    Uart->write((byte)STRING);
                    while(n <= Number)
                    {
                        Uart->print(Str[Addr+n]);
                        Uart->write(0x03);
                        n++;
                    }
                    return;
                break;
                case DIAGNOSTICS :
                       if((Addr+Number) > Diagnostics_Size) 
                    {
                        WriteCode(SizeOverFlow);
                        return;
                    }
                   
                    Uart->write((byte)Header);
                    Uart->write((byte)Sta);
                    Uart->write((byte)DIAGNOSTICS);
                    while(n <= Number)
                    {
                        Uart->write((byte)Diag[Addr+n]);
                        n++;
                    }
                    return;
                break;
                default :        
                    WriteCode(AddressNotSupprt);
        }
   
}

void ProtocolEx::WriteCode(command cmd)
{
    Uart->write((byte)Header);
    Uart->write((byte)cmd);
}


void ProtocolEx::GetSize()
{
                    Uart->write((byte)Header);
                    Uart->write((byte)Sta);
                    Uart->write((byte)SizeOptimize);
                    
                    TypeConvert.GetUInt = (uint16_t)InPut_Size;
                    Uart->write(TypeConvert.SetByte[1]);
                    Uart->write(TypeConvert.SetByte[0]);
                    
                    TypeConvert.GetUInt = (uint16_t)OutPut_Size;
                    Uart->write(TypeConvert.SetByte[1]);
                    Uart->write(TypeConvert.SetByte[0]);
                    
                    TypeConvert.GetUInt = (uint16_t)Int_Size;
                    Uart->write(TypeConvert.SetByte[1]);
                    Uart->write(TypeConvert.SetByte[0]);
                    
                    TypeConvert.GetUInt = (uint16_t)Uint_Size;
                    Uart->write(TypeConvert.SetByte[1]);
                    Uart->write(TypeConvert.SetByte[0]);

                    TypeConvert.GetUInt = (uint16_t)Float_Size;
                    Uart->write(TypeConvert.SetByte[1]);
                    Uart->write(TypeConvert.SetByte[0]);

                    
                    TypeConvert.GetUInt = (uint16_t)String_Size;
                    Uart->write(TypeConvert.SetByte[1]);
                    Uart->write(TypeConvert.SetByte[0]);

                    TypeConvert.GetUInt = (uint16_t)Diagnostics_Size;
                    Uart->write(TypeConvert.SetByte[1]);
                    Uart->write(TypeConvert.SetByte[0]);
}


void ProtocolEx::FillText(byte Address,String Message)
{
    int Count = Message.length();
    int Index = 0;

    memset(&Str[Address][0],0,Ascii_Size);

    while(Index <= Count)
    {
        Str[Address][Index] = Message.charAt(Index);
        Index++;
    }
}
