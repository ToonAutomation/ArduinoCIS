# ArduinoCIS 


ProtocolEX With CIS Design

Support:
Communication RS232 , RS485 

Define Symbol Address                                     
I = Input               Size 1 word       
Q = Output              Size 1 word        
Int = Integer           Size 1 word        
Uint = Unsigned Integer Size 1 word        
Float = float           Size 4 word        
Str = string            Size 1 bytex16     
Diag = Unsigned Integer Size 1 word        

Default Size Address 
I[0] - I[15]  : 16 word or 256 Bit
Q[0] - Q[15]  : 16 word or  256 Bit
Int[0] - Int[31]  : 32 word 
UInt[0] - UInt[31]  : 32 word 
Float[0] - Float[31] : 32 Data
Str[0] - Str[31] : 32 Data message Max 16 Char/Data  
Diag[0] - Diag[15] : 16 word or  256 Bit
