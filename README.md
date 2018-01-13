# ArduinoCIS 


ProtocolEX With CIS Design

Support:
Communication RS232 , RS485 

Address                                    Default Address
I = Input               Size 1 word        I[0] - I[15]  : Input 16 word or 256 Bit
Q = Output              Size 1 word        Q[0] - Q[15]  : Output 16 word or  256 Bit
Int = Integer           Size 1 word        Int[0] - Int[31]  : Integer 32 word 
Uint = Unsigned Integer Size 1 word        UInt[0] - UInt[31]  : Unsigned Integer 32 word 
Float = float           Size 4 word        Float[0] - Float[31] : float 32 Data
Str = string            Size 1 bytex16     Str[0] - Str[31] : string 32 Data message Max 16 Char/Data  
Diag = Unsigned Integer Size 1 word        Diag[0] - Diag[15] : Diagnostics 16 word or  256 Bit
