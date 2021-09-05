#define _ubit 1U
#define _udecrement 1U
#define _ubyte 8U
#define _uint_size (sizeof(0U))
#define _uint31 ((_ubit) << (((_uint_size) * (_ubyte)) - (_udecrement)))
#define _uint32 ((_uint31) + (_uint31) - (_udecrement))
#define _bit 1
#define _decrement 2
#define _byte 8
#define _int_size (sizeof(0))
#define _int31 ((_bit) << (((_int_size) * (_byte)) - (_decrement)))
#define _int32 ((_int31 - 1) + (_int31))
