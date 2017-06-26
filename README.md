libvle
======

a simple library to disassemble PowerPC VLE instructions.

# example

```c

vle_handle handle;
// initialize the handler
if (vle_init(&handle, buffer, size) != 0) {
	printf("failed to initialize handle\n");
	return;
}
// loop on vle_next
while((instr = vle_next(&handle))) {
	printf ("%s ", instr->name);
	for (j = 0; j < instr->n; ++j) {
		if (instr->fields[j].type == TYPE_REG) {
			printf ("r%-2u ", instr->fields[j].value);
		} else if (instr->fields[j].type == TYPE_IMM) {
			printf ("0x%x ", instr->fields[j].value);
		} else if (instr->fields[j].type == TYPE_MEM)  {
			printf ("0x%x(r%d) ", instr->fields[j + 1].value, instr->fields[j].value);
			j++;
		} else if (instr->fields[j].type == TYPE_JMP) {
			printf ("0x%x ", instr->fields[j].value);
		} else if (instr->fields[j].type == TYPE_CR) {
			printf ("cr%u ", instr->fields[j].value);
		}
	}
	printf ("\n");
	// always free the instruction via the method.
	vle_free(instr);
};
```

### output

```
se_bmaski r7 0x10
e_lis r6 0xfffc3fe
e_li r0 0x5af0
se_slwi r3 0x1c
se_or r0 r3
e_add16i r6 r6 0xffffc000
se_stw r0 0x4(r6)
se_or r0 r3
se_mtar r16 r7
se_stw r0 0x4(r6)
se_lwz r0 0x0(r6)
se_btsti r0 0x4
se_bne 0xfffffe04
se_blr  

```
