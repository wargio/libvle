[![Build Status](https://travis-ci.org/wargio/libvle.svg?branch=master)](https://travis-ci.org/wargio/libvle)

libvle
======

a simple library to disassemble PowerPC VLE instructions.

# example

```c

// initialize the handler
ut32 start_address = 0x08004000
vle_t* instr = NULL;
vle_handle handle;
if (vle_init(&handle, buffer, size, start_address)) {
	printf("failed to initialize handle\n");
	return;
}

// loop on vle_next
while((instr = vle_next(&handle))) {
	vle_snprint(tmp, 256, instr);
	printf ("%s\n", tmp);
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
