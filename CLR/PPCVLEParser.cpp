#include "PPCVLEParser.h"
#include "vle.h"

VLEt^ PPCVLEParser::DecodeOne(array<System::Byte>^ buf, System::Int32 adr, System::UInt32 base) {
	pin_ptr<ut8> bufptr = &buf[adr];

	vle_t* instr_n = vle_decode_one(bufptr, buf->Length, base);
	if (instr_n == 0) {
		return nullptr;
	}

	array<VLEFieldt^>^ fields_m = gcnew array<VLEFieldt^>(instr_n->n);
	for (int i = 0; i < instr_n->n; i++) {
		VLEFieldt^ field_m = gcnew VLEFieldt();
		field_m->value = instr_n->fields[i].value;
		field_m->type = (VLEType)instr_n->fields[i].type;
		fields_m->SetValue(field_m, i);
	}
	VLEt^ instr_m = gcnew VLEt();
	instr_m->fields = fields_m;
	instr_m->size = instr_n->size;
	instr_m->name = gcnew System::String(instr_n->name);
	vle_free(instr_n);

	return instr_m;
}
