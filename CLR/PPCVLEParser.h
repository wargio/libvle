#pragma once
#include "vle.h"
public enum class VLEType {
	NONE = TYPE_NONE, REG = TYPE_REG, IMM = TYPE_IMM, MEM = TYPE_MEM, JMP = TYPE_JMP, CR = TYPE_CR
};


public ref class VLEFieldt {
public:
	System::UInt32 value;
	VLEType type;
};

public ref class VLEt {
public:
	System::String^ name;
	array<VLEFieldt^>^ fields;
	System::UInt16 size;
};

public ref class PPCVLEParser {
public:
	static VLEt^ DecodeOne(array<System::Byte>^ buf, System::Int32 adr, System::UInt32 base);
};
