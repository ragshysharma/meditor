; Listing generated by Microsoft (R) Optimizing Compiler Version 16.00.30319.01 

	TITLE	H:\MinGW\home\other\meditor2\Libs\7z\Archive\7z\7zDecode.c
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	_allocMain$GSCopy$
PUBLIC	__$ArrayPad$
EXTRN	_LzmaDec_FreeProbs:PROC
EXTRN	_LzmaDec_DecodeToDic:PROC
EXTRN	_LzmaDec_Init:PROC
EXTRN	_LzmaDec_AllocateProbs:PROC
EXTRN	___security_cookie:DWORD
EXTRN	@__security_check_cookie@4:PROC
; Function compile flags: /Ogtp
; File h:\mingw\home\other\meditor2\libs\7z\archive\7z\7zdecode.c
;	COMDAT _SzDecodeLzma
_TEXT	SEGMENT
_status$80244 = -136					; size = 4
_allocMain$GSCopy$ = -132				; size = 4
_inBuf$80233 = -128					; size = 4
_inProcessed$80241 = -124				; size = 4
_lookahead$80235 = -120					; size = 4
_state$ = -116						; size = 112
__$ArrayPad$ = -4					; size = 4
_coder$ = 8						; size = 4
_inSize$ = 12						; size = 8
_outSize$ = 20						; size = 4
_SzDecodeLzma PROC					; COMDAT
; _inStream$ = ebx
; _outBuffer$ = edx
; _allocMain$ = ecx

; 18   : {

	push	ebp
	mov	ebp, esp
	sub	esp, 136				; 00000088H
	mov	eax, DWORD PTR ___security_cookie
	xor	eax, ebp
	mov	DWORD PTR __$ArrayPad$[ebp], eax
	mov	eax, DWORD PTR _coder$[ebp]
	push	esi
	push	edi

; 19   :   CLzmaDec state;
; 20   :   SRes res = SZ_OK;
; 21   : 
; 22   :   LzmaDec_Construct(&state);
; 23   :   RINOK(LzmaDec_AllocateProbs(&state, coder->Props.data, (unsigned)coder->Props.size, allocMain));

	push	ecx

; 56   :         break;
; 57   :     }
; 58   :   }

	mov	DWORD PTR _allocMain$GSCopy$[ebp], ecx
	mov	ecx, DWORD PTR [eax+20]
	mov	esi, edx
	mov	edx, DWORD PTR [eax+16]
	push	ecx
	push	edx
	lea	eax, DWORD PTR _state$[ebp]
	xor	edi, edi
	push	eax
	mov	DWORD PTR _state$[ebp+20], edi
	mov	DWORD PTR _state$[ebp+16], edi
	call	_LzmaDec_AllocateProbs
	add	esp, 16					; 00000010H
	cmp	eax, edi
	jne	$LN12@SzDecodeLz

; 24   :   state.dic = outBuffer;
; 25   :   state.dicBufSize = outSize;
; 26   :   LzmaDec_Init(&state);

	mov	ecx, DWORD PTR _outSize$[ebp]
	lea	edx, DWORD PTR _state$[ebp]
	push	edx
	mov	DWORD PTR _state$[ebp+20], esi
	mov	DWORD PTR _state$[ebp+40], ecx
	call	_LzmaDec_Init
	add	esp, 4
	npad	6
$LL10@SzDecodeLz:

; 27   : 
; 28   :   for (;;)
; 29   :   {
; 30   :     Byte *inBuf = NULL;
; 31   :     size_t lookahead = (1 << 18);

	mov	eax, 262144				; 00040000H
	mov	DWORD PTR _inBuf$80233[ebp], edi
	mov	DWORD PTR _lookahead$80235[ebp], eax

; 32   :     if (lookahead > inSize)

	cmp	DWORD PTR _inSize$[ebp+4], edi
	ja	SHORT $LN8@SzDecodeLz
	jb	SHORT $LN20@SzDecodeLz
	cmp	DWORD PTR _inSize$[ebp], eax
	jae	SHORT $LN8@SzDecodeLz
$LN20@SzDecodeLz:

; 33   :       lookahead = (size_t)inSize;

	mov	eax, DWORD PTR _inSize$[ebp]
	mov	DWORD PTR _lookahead$80235[ebp], eax
$LN8@SzDecodeLz:

; 34   :     res = inStream->Look((void *)inStream, (void **)&inBuf, &lookahead);

	mov	eax, DWORD PTR [ebx]
	lea	ecx, DWORD PTR _lookahead$80235[ebp]
	push	ecx
	lea	edx, DWORD PTR _inBuf$80233[ebp]
	push	edx
	push	ebx
	call	eax
	mov	esi, eax
	add	esp, 12					; 0000000cH

; 35   :     if (res != SZ_OK)

	cmp	esi, edi
	jne	$LN23@SzDecodeLz

; 36   :       break;
; 37   : 
; 38   :     {
; 39   :       SizeT inProcessed = (SizeT)lookahead, dicPos = state.dicPos;

	mov	ecx, DWORD PTR _lookahead$80235[ebp]
	mov	edi, DWORD PTR _state$[ebp+36]

; 40   :       ELzmaStatus status;
; 41   :       res = LzmaDec_DecodeToDic(&state, outSize, inBuf, &inProcessed, LZMA_FINISH_END, &status);

	lea	edx, DWORD PTR _status$80244[ebp]
	push	edx
	mov	edx, DWORD PTR _outSize$[ebp]
	push	1
	lea	eax, DWORD PTR _inProcessed$80241[ebp]
	push	eax
	mov	DWORD PTR _inProcessed$80241[ebp], ecx
	mov	ecx, DWORD PTR _inBuf$80233[ebp]
	push	ecx
	push	edx
	lea	eax, DWORD PTR _state$[ebp]
	push	eax
	call	_LzmaDec_DecodeToDic
	mov	esi, eax

; 42   :       lookahead -= inProcessed;

	mov	eax, DWORD PTR _inProcessed$80241[ebp]
	sub	DWORD PTR _lookahead$80235[ebp], eax
	add	esp, 24					; 00000018H

; 43   :       inSize -= inProcessed;

	sub	DWORD PTR _inSize$[ebp], eax
	sbb	DWORD PTR _inSize$[ebp+4], 0

; 44   :       if (res != SZ_OK)

	test	esi, esi
	jne	SHORT $LN23@SzDecodeLz

; 45   :         break;
; 46   :       if (state.dicPos == state.dicBufSize || (inProcessed == 0 && dicPos == state.dicPos))

	mov	ecx, DWORD PTR _state$[ebp+40]
	cmp	DWORD PTR _state$[ebp+36], ecx
	je	SHORT $LN21@SzDecodeLz
	test	eax, eax
	jne	SHORT $LN5@SzDecodeLz
	cmp	edi, DWORD PTR _state$[ebp+36]
	je	SHORT $LN21@SzDecodeLz
$LN5@SzDecodeLz:

; 52   :         break;
; 53   :       }
; 54   :       res = inStream->Skip((void *)inStream, inProcessed);

	mov	ecx, DWORD PTR [ebx+4]
	push	eax
	push	ebx
	call	ecx
	mov	esi, eax
	add	esp, 8

; 55   :       if (res != SZ_OK)

	test	esi, esi
	jne	SHORT $LN23@SzDecodeLz

; 56   :         break;
; 57   :     }
; 58   :   }

	xor	edi, edi
	jmp	$LL10@SzDecodeLz
$LN21@SzDecodeLz:

; 47   :       {
; 48   :         if (state.dicBufSize != outSize || lookahead != 0 ||
; 49   :             (status != LZMA_STATUS_FINISHED_WITH_MARK &&
; 50   :              status != LZMA_STATUS_MAYBE_FINISHED_WITHOUT_MARK))

	cmp	ecx, DWORD PTR _outSize$[ebp]
	jne	SHORT $LN22@SzDecodeLz
	cmp	DWORD PTR _lookahead$80235[ebp], 0
	jne	SHORT $LN22@SzDecodeLz
	mov	eax, DWORD PTR _status$80244[ebp]
	cmp	eax, 1
	je	SHORT $LN23@SzDecodeLz
	cmp	eax, 4
	je	SHORT $LN23@SzDecodeLz
$LN22@SzDecodeLz:

; 51   :           res = SZ_ERROR_DATA;

	mov	esi, 1
$LN23@SzDecodeLz:

; 59   : 
; 60   :   LzmaDec_FreeProbs(&state, allocMain);

	mov	edx, DWORD PTR _allocMain$GSCopy$[ebp]
	push	edx
	lea	eax, DWORD PTR _state$[ebp]
	push	eax
	call	_LzmaDec_FreeProbs
	add	esp, 8

; 61   :   return res;

	mov	eax, esi
$LN12@SzDecodeLz:

; 62   : }

	mov	ecx, DWORD PTR __$ArrayPad$[ebp]
	pop	edi
	xor	ecx, ebp
	pop	esi
	call	@__security_check_cookie@4
	mov	esp, ebp
	pop	ebp
	ret	0
_SzDecodeLzma ENDP
_TEXT	ENDS
EXTRN	_memcpy:PROC
; Function compile flags: /Ogtp
;	COMDAT _SzDecodeCopy
_TEXT	SEGMENT
_inBuf$80263 = -4					; size = 4
_inSize$ = 8						; size = 8
_curSize$80264 = 12					; size = 4
_outBuffer$ = 16					; size = 4
_SzDecodeCopy PROC					; COMDAT
; _inStream$ = esi

; 65   : {

	push	ebp
	mov	ebp, esp
	push	ecx
	push	ebx

; 66   :   while (inSize > 0)

	mov	ebx, DWORD PTR _inSize$[ebp]
	push	edi
	mov	edi, DWORD PTR _inSize$[ebp+4]
	test	edi, edi
	jne	SHORT $LL6@SzDecodeCo
	test	ebx, ebx
	je	SHORT $LN5@SzDecodeCo
$LL6@SzDecodeCo:

; 67   :   {
; 68   :     void *inBuf;
; 69   :     size_t curSize = (1 << 18);

	mov	DWORD PTR _curSize$80264[ebp], 262144	; 00040000H

; 70   :     if (curSize > inSize)

	test	edi, edi
	ja	SHORT $LN4@SzDecodeCo
	jb	SHORT $LN14@SzDecodeCo
	cmp	ebx, 262144				; 00040000H
	jae	SHORT $LN4@SzDecodeCo
$LN14@SzDecodeCo:

; 71   :       curSize = (size_t)inSize;

	mov	DWORD PTR _curSize$80264[ebp], ebx
$LN4@SzDecodeCo:

; 72   :     RINOK(inStream->Look((void *)inStream, (void **)&inBuf, &curSize));

	mov	edx, DWORD PTR [esi]
	lea	eax, DWORD PTR _curSize$80264[ebp]
	push	eax
	lea	ecx, DWORD PTR _inBuf$80263[ebp]
	push	ecx
	push	esi
	call	edx
	add	esp, 12					; 0000000cH
	test	eax, eax
	jne	SHORT $LN7@SzDecodeCo

; 73   :     if (curSize == 0)

	mov	eax, DWORD PTR _curSize$80264[ebp]
	test	eax, eax
	je	SHORT $LN11@SzDecodeCo

; 75   :     memcpy(outBuffer, inBuf, curSize);

	mov	ecx, DWORD PTR _outBuffer$[ebp]
	push	eax
	mov	eax, DWORD PTR _inBuf$80263[ebp]
	push	eax
	push	ecx
	call	_memcpy

; 76   :     outBuffer += curSize;

	mov	eax, DWORD PTR _curSize$80264[ebp]
	add	DWORD PTR _outBuffer$[ebp], eax

; 77   :     inSize -= curSize;
; 78   :     RINOK(inStream->Skip((void *)inStream, curSize));

	mov	edx, DWORD PTR [esi+4]
	push	eax
	sub	ebx, eax
	push	esi
	sbb	edi, 0
	call	edx
	add	esp, 20					; 00000014H
	test	eax, eax
	jne	SHORT $LN7@SzDecodeCo

; 66   :   while (inSize > 0)

	test	edi, edi
	ja	SHORT $LL6@SzDecodeCo
	jb	SHORT $LN5@SzDecodeCo
	test	ebx, ebx
	jne	SHORT $LL6@SzDecodeCo
$LN5@SzDecodeCo:

; 79   :   }
; 80   :   return SZ_OK;

	xor	eax, eax
$LN7@SzDecodeCo:
	pop	edi
	pop	ebx

; 81   : }

	mov	esp, ebp
	pop	ebp
	ret	0
$LN11@SzDecodeCo:
	pop	edi

; 74   :       return SZ_ERROR_INPUT_EOF;

	mov	eax, 6
	pop	ebx

; 81   : }

	mov	esp, ebp
	pop	ebp
	ret	0
_SzDecodeCopy ENDP
_TEXT	ENDS
PUBLIC	_CheckSupportedFolder
; Function compile flags: /Ogtp
;	COMDAT _CheckSupportedFolder
_TEXT	SEGMENT
_f$ = 8							; size = 4
_CheckSupportedFolder PROC				; COMDAT

; 89   : {

	push	ebp
	mov	ebp, esp
	push	ebx

; 90   :   if (f->NumCoders < 1 || f->NumCoders > 4)

	mov	ebx, DWORD PTR _f$[ebp]
	push	edi
	mov	edi, DWORD PTR [ebx+16]
	cmp	edi, 1
	jb	$LN18@CheckSuppo
	cmp	edi, 4
	ja	$LN18@CheckSuppo

; 92   :   if (IS_UNSUPPORTED_CODER(f->Coders[0]))

	mov	ecx, DWORD PTR [ebx]
	mov	edx, DWORD PTR [ecx+8]
	push	esi
	mov	esi, DWORD PTR [ecx+12]
	mov	eax, edx
	or	eax, esi
	je	SHORT $LN22@CheckSuppo
	cmp	edx, 196865				; 00030101H
	jne	$LN16@CheckSuppo
	test	esi, esi
	jne	$LN16@CheckSuppo
$LN22@CheckSuppo:
	mov	eax, 1
	cmp	DWORD PTR [ecx], eax
	jne	$LN16@CheckSuppo
	cmp	DWORD PTR [ecx+4], eax
	jne	$LN16@CheckSuppo

; 94   :   if (f->NumCoders == 1)

	cmp	edi, eax
	jne	SHORT $LN14@CheckSuppo

; 95   :   {
; 96   :     if (f->NumPackStreams != 1 || f->PackStreams[0] != 0 || f->NumBindPairs != 0)

	cmp	DWORD PTR [ebx+24], eax
	jne	$LN16@CheckSuppo
	mov	ecx, DWORD PTR [ebx+8]
	cmp	DWORD PTR [ecx], 0
	jne	$LN16@CheckSuppo
	cmp	DWORD PTR [ebx+20], 0
$LN27@CheckSuppo:
	jne	$LN16@CheckSuppo

; 106  :       return SZ_ERROR_UNSUPPORTED;
; 107  :     return SZ_OK;

	pop	esi
	pop	edi
	xor	eax, eax
	pop	ebx

; 125  :     return SZ_OK;
; 126  :   }
; 127  :   return SZ_ERROR_UNSUPPORTED;
; 128  : }

	pop	ebp
	ret	0
$LN14@CheckSuppo:

; 97   :       return SZ_ERROR_UNSUPPORTED;
; 98   :     return SZ_OK;
; 99   :   }
; 100  :   if (f->NumCoders == 2)

	cmp	edi, 2
	jne	SHORT $LN11@CheckSuppo

; 101  :   {
; 102  :     if (IS_NO_BCJ(f->Coders[1]) ||
; 103  :         f->NumPackStreams != 1 || f->PackStreams[0] != 0 ||
; 104  :         f->NumBindPairs != 1 ||
; 105  :         f->BindPairs[0].InIndex != 1 || f->BindPairs[0].OutIndex != 0)

	cmp	DWORD PTR [ecx+32], 50528515		; 03030103H
	jne	$LN16@CheckSuppo
	cmp	DWORD PTR [ecx+36], 0
	jne	$LN16@CheckSuppo
	cmp	DWORD PTR [ecx+24], eax
	jne	$LN16@CheckSuppo
	cmp	DWORD PTR [ecx+28], eax
	jne	$LN16@CheckSuppo
	cmp	DWORD PTR [ebx+24], eax
	jne	$LN16@CheckSuppo
	mov	edx, DWORD PTR [ebx+8]
	cmp	DWORD PTR [edx], 0
	jne	$LN16@CheckSuppo
	cmp	DWORD PTR [ebx+20], eax
	jne	$LN16@CheckSuppo
	mov	ecx, DWORD PTR [ebx+4]
	cmp	DWORD PTR [ecx], eax
	jne	$LN16@CheckSuppo
	cmp	DWORD PTR [ecx+4], 0

; 106  :       return SZ_ERROR_UNSUPPORTED;
; 107  :     return SZ_OK;

	jmp	SHORT $LN27@CheckSuppo
$LN11@CheckSuppo:

; 108  :   }
; 109  :   if (f->NumCoders == 4)

	cmp	edi, 4
	jne	$LN16@CheckSuppo

; 110  :   {
; 111  :     if (IS_UNSUPPORTED_CODER(f->Coders[1]) ||
; 112  :         IS_UNSUPPORTED_CODER(f->Coders[2]) ||
; 113  :         IS_NO_BCJ2(f->Coders[3]))

	mov	edx, DWORD PTR [ecx+32]
	mov	esi, DWORD PTR [ecx+36]
	mov	edi, edx
	or	edi, esi
	je	SHORT $LN5@CheckSuppo
	cmp	edx, 196865				; 00030101H
	jne	$LN24@CheckSuppo
	test	esi, esi
	jne	$LN24@CheckSuppo
$LN5@CheckSuppo:
	cmp	DWORD PTR [ecx+24], eax
	jne	$LN24@CheckSuppo
	cmp	DWORD PTR [ecx+28], eax
	jne	$LN24@CheckSuppo
	mov	edx, DWORD PTR [ecx+56]
	mov	esi, DWORD PTR [ecx+60]
	mov	edi, edx
	or	edi, esi
	je	SHORT $LN23@CheckSuppo
	cmp	edx, 196865				; 00030101H
	jne	SHORT $LN24@CheckSuppo
	test	esi, esi
	jne	SHORT $LN24@CheckSuppo
$LN23@CheckSuppo:
	cmp	DWORD PTR [ecx+48], eax
	jne	SHORT $LN24@CheckSuppo
	cmp	DWORD PTR [ecx+52], eax
	jne	SHORT $LN24@CheckSuppo
	cmp	DWORD PTR [ecx+80], 50528539		; 0303011bH
	jne	SHORT $LN24@CheckSuppo
	cmp	DWORD PTR [ecx+84], 0
	jne	SHORT $LN24@CheckSuppo
	mov	esi, 4
	cmp	DWORD PTR [ecx+72], esi
	jne	SHORT $LN3@CheckSuppo
	cmp	DWORD PTR [ecx+76], eax
	jne	SHORT $LN3@CheckSuppo

; 115  :     if (f->NumPackStreams != 4 ||
; 116  :         f->PackStreams[0] != 2 ||
; 117  :         f->PackStreams[1] != 6 ||
; 118  :         f->PackStreams[2] != 1 ||
; 119  :         f->PackStreams[3] != 0 ||
; 120  :         f->NumBindPairs != 3 ||
; 121  :         f->BindPairs[0].InIndex != 5 || f->BindPairs[0].OutIndex != 0 ||
; 122  :         f->BindPairs[1].InIndex != 4 || f->BindPairs[1].OutIndex != 1 ||
; 123  :         f->BindPairs[2].InIndex != 3 || f->BindPairs[2].OutIndex != 2)

	cmp	DWORD PTR [ebx+24], esi
	jne	SHORT $LN3@CheckSuppo
	mov	ecx, DWORD PTR [ebx+8]
	cmp	DWORD PTR [ecx], 2
	jne	SHORT $LN3@CheckSuppo
	cmp	DWORD PTR [ecx+4], 6
	jne	SHORT $LN3@CheckSuppo
	cmp	DWORD PTR [ecx+8], eax
	jne	SHORT $LN3@CheckSuppo
	cmp	DWORD PTR [ecx+12], 0
	jne	SHORT $LN3@CheckSuppo
	mov	edx, 3
	cmp	DWORD PTR [ebx+20], edx
	jne	SHORT $LN3@CheckSuppo
	mov	ecx, DWORD PTR [ebx+4]
	cmp	DWORD PTR [ecx], 5
	jne	SHORT $LN3@CheckSuppo
	cmp	DWORD PTR [ecx+4], 0
	jne	SHORT $LN3@CheckSuppo
	cmp	DWORD PTR [ecx+8], esi
	jne	SHORT $LN3@CheckSuppo
	cmp	DWORD PTR [ecx+12], eax
	jne	SHORT $LN3@CheckSuppo
	cmp	DWORD PTR [ecx+16], edx
	jne	SHORT $LN3@CheckSuppo
	cmp	DWORD PTR [ecx+20], 2
	jne	SHORT $LN3@CheckSuppo

; 106  :       return SZ_ERROR_UNSUPPORTED;
; 107  :     return SZ_OK;

	pop	esi
	pop	edi
	xor	eax, eax
	pop	ebx

; 125  :     return SZ_OK;
; 126  :   }
; 127  :   return SZ_ERROR_UNSUPPORTED;
; 128  : }

	pop	ebp
	ret	0
$LN24@CheckSuppo:

; 124  :       return SZ_ERROR_UNSUPPORTED;

	mov	esi, 4
$LN3@CheckSuppo:

; 114  :       return SZ_ERROR_UNSUPPORTED;

	mov	eax, esi
	pop	esi
	pop	edi
	pop	ebx

; 125  :     return SZ_OK;
; 126  :   }
; 127  :   return SZ_ERROR_UNSUPPORTED;
; 128  : }

	pop	ebp
	ret	0
$LN16@CheckSuppo:
	pop	esi
	pop	edi

; 93   :     return SZ_ERROR_UNSUPPORTED;

	mov	eax, 4
	pop	ebx

; 125  :     return SZ_OK;
; 126  :   }
; 127  :   return SZ_ERROR_UNSUPPORTED;
; 128  : }

	pop	ebp
	ret	0
$LN18@CheckSuppo:
	pop	edi

; 91   :     return SZ_ERROR_UNSUPPORTED;

	mov	eax, 4
	pop	ebx

; 125  :     return SZ_OK;
; 126  :   }
; 127  :   return SZ_ERROR_UNSUPPORTED;
; 128  : }

	pop	ebp
	ret	0
_CheckSupportedFolder ENDP
_TEXT	ENDS
PUBLIC	_GetSum
; Function compile flags: /Ogtp
;	COMDAT _GetSum
_TEXT	SEGMENT
_sum$ = -16						; size = 8
$T80479 = -8						; size = 8
_values$ = 8						; size = 4
_index$ = 12						; size = 4
_GetSum	PROC						; COMDAT

; 131  : {

	push	ebp
	mov	ebp, esp
	sub	esp, 16					; 00000010H

; 132  :   UInt64 sum = 0;
; 133  :   UInt32 i;
; 134  :   for (i = 0; i < index; i++)

	mov	edx, DWORD PTR _index$[ebp]
	push	ebx
	push	esi
	mov	esi, DWORD PTR _values$[ebp]
	xor	ecx, ecx
	push	edi
	xor	edi, edi
	xor	ebx, ebx
	mov	DWORD PTR $T80479[ebp], ecx
	mov	DWORD PTR $T80479[ebp+4], ecx
	mov	DWORD PTR _sum$[ebp], ecx
	mov	DWORD PTR _sum$[ebp+4], ecx
	cmp	edx, 2
	jl	SHORT $LC9@GetSum
	npad	10
$LL11@GetSum:

; 135  :     sum += values[i];

	add	edi, DWORD PTR [esi+ecx*8]
	mov	eax, DWORD PTR [esi+ecx*8+8]
	adc	ebx, DWORD PTR [esi+ecx*8+4]
	add	DWORD PTR $T80479[ebp], eax
	mov	edx, DWORD PTR [esi+ecx*8+12]
	adc	DWORD PTR $T80479[ebp+4], edx
	mov	edx, DWORD PTR _index$[ebp]
	add	ecx, 2
	lea	eax, DWORD PTR [edx-1]
	cmp	ecx, eax
	jb	SHORT $LL11@GetSum
$LC9@GetSum:

; 132  :   UInt64 sum = 0;
; 133  :   UInt32 i;
; 134  :   for (i = 0; i < index; i++)

	cmp	ecx, edx
	jae	SHORT $LN8@GetSum

; 135  :     sum += values[i];

	mov	eax, DWORD PTR [esi+ecx*8]
	mov	ecx, DWORD PTR [esi+ecx*8+4]
	mov	DWORD PTR _sum$[ebp], eax
	mov	DWORD PTR _sum$[ebp+4], ecx
$LN8@GetSum:
	mov	eax, DWORD PTR $T80479[ebp]
	mov	edx, DWORD PTR $T80479[ebp+4]
	add	eax, edi
	adc	edx, ebx
	add	eax, DWORD PTR _sum$[ebp]
	pop	edi
	adc	edx, DWORD PTR _sum$[ebp+4]
	pop	esi
	pop	ebx

; 136  :   return sum;
; 137  : }

	mov	esp, ebp
	pop	ebp
	ret	0
_GetSum	ENDP
_TEXT	ENDS
PUBLIC	_tempBuf$GSCopy$
PUBLIC	_allocMain$GSCopy$
PUBLIC	_outSize$GSCopy$
PUBLIC	_folder$GSCopy$
PUBLIC	_outBuffer$GSCopy$
PUBLIC	_inStream$GSCopy$
PUBLIC	_packSizes$GSCopy$
PUBLIC	__$ArrayPad$
PUBLIC	_SzDecode2
EXTRN	_Bcj2_Decode:PROC
EXTRN	_LookInStream_SeekTo:PROC
EXTRN	_x86_Convert:PROC
; Function compile flags: /Ogtp
;	COMDAT _SzDecode2
_TEXT	SEGMENT
_coder$80336 = -76					; size = 4
_tempBuf3$ = -72					; size = 4
_tempSize3$ = -68					; size = 4
_tempBuf$GSCopy$ = -64					; size = 4
_allocMain$GSCopy$ = -60				; size = 4
_folder$GSCopy$ = -56					; size = 4
_packSizes$GSCopy$ = -52				; size = 4
_ci$ = -48						; size = 4
_outBuffer$GSCopy$ = -44				; size = 4
_inStream$GSCopy$ = -40					; size = 4
_outSize$GSCopy$ = -36					; size = 4
_state$80370 = -32					; size = 4
_outSizeCur$80343 = -32					; size = 4
_indices$80345 = -28					; size = 12
_tempSizes$ = -16					; size = 12
__$ArrayPad$ = -4					; size = 4
_packSizes$ = 8						; size = 4
_folder$ = 12						; size = 4
_inStream$ = 16						; size = 4
_startPos$ = 20						; size = 8
_outBuffer$ = 28					; size = 4
_outSize$ = 32						; size = 4
_allocMain$ = 36					; size = 4
_tempBuf$ = 40						; size = 4
_SzDecode2 PROC						; COMDAT

; 143  : {

	push	ebp
	mov	ebp, esp
	sub	esp, 76					; 0000004cH
	mov	eax, DWORD PTR ___security_cookie
	xor	eax, ebp
	mov	DWORD PTR __$ArrayPad$[ebp], eax

; 185  :         }
; 186  :         else
; 187  :           return SZ_ERROR_UNSUPPORTED;

	mov	eax, DWORD PTR _packSizes$[ebp]
	mov	ecx, DWORD PTR _inStream$[ebp]
	mov	edx, DWORD PTR _outBuffer$[ebp]
	push	esi
	mov	esi, DWORD PTR _folder$[ebp]
	push	edi
	xor	edi, edi
	mov	DWORD PTR _packSizes$GSCopy$[ebp], eax
	mov	eax, DWORD PTR _outSize$[ebp]
	mov	DWORD PTR _inStream$GSCopy$[ebp], ecx
	mov	ecx, DWORD PTR _allocMain$[ebp]
	mov	DWORD PTR _outBuffer$GSCopy$[ebp], edx
	mov	edx, DWORD PTR _tempBuf$[ebp]
	push	esi
	mov	DWORD PTR _folder$GSCopy$[ebp], esi
	mov	DWORD PTR _outSize$GSCopy$[ebp], eax
	mov	DWORD PTR _allocMain$GSCopy$[ebp], ecx
	mov	DWORD PTR _tempBuf$GSCopy$[ebp], edx
	mov	DWORD PTR _tempSizes$[ebp], edi
	mov	DWORD PTR _tempSizes$[ebp+4], edi
	mov	DWORD PTR _tempSize3$[ebp], edi
	mov	DWORD PTR _tempBuf3$[ebp], edi
	call	_CheckSupportedFolder
	add	esp, 4
	cmp	eax, edi
	jne	SHORT $LN33@SzDecode2

; 144  :   UInt32 ci;
; 145  :   SizeT tempSizes[3] = { 0, 0, 0};
; 146  :   SizeT tempSize3 = 0;
; 147  :   Byte *tempBuf3 = 0;
; 148  : 
; 149  :   RINOK(CheckSupportedFolder(folder));
; 150  : 
; 151  :   for (ci = 0; ci < folder->NumCoders; ci++)

	mov	edx, DWORD PTR [esi+16]
	xor	eax, eax
	push	ebx
	mov	DWORD PTR _ci$[ebp], eax
	cmp	edx, edi
	ja	SHORT $LN31@SzDecode2
$LN58@SzDecode2:
	pop	ebx
$LN33@SzDecode2:
	pop	edi
	pop	esi

; 241  : }

	mov	ecx, DWORD PTR __$ArrayPad$[ebp]
	xor	ecx, ebp
	call	@__security_check_cookie@4
	mov	esp, ebp
	pop	ebp
	ret	0
$LL53@SzDecode2:

; 144  :   UInt32 ci;
; 145  :   SizeT tempSizes[3] = { 0, 0, 0};
; 146  :   SizeT tempSize3 = 0;
; 147  :   Byte *tempBuf3 = 0;
; 148  : 
; 149  :   RINOK(CheckSupportedFolder(folder));
; 150  : 
; 151  :   for (ci = 0; ci < folder->NumCoders; ci++)

	mov	eax, DWORD PTR _ci$[ebp]
$LN31@SzDecode2:

; 152  :   {
; 153  :     CSzCoderInfo *coder = &folder->Coders[ci];

	mov	edi, DWORD PTR [esi]
	lea	ecx, DWORD PTR [eax+eax*2]
	lea	ecx, DWORD PTR [edi+ecx*8]

; 154  : 
; 155  :     if (coder->MethodID == k_Copy || coder->MethodID == k_LZMA)

	mov	edi, DWORD PTR [ecx+8]
	mov	DWORD PTR _coder$80336[ebp], ecx
	mov	ecx, DWORD PTR [ecx+12]
	mov	ebx, edi
	or	ebx, ecx
	je	$LN56@SzDecode2
	cmp	edi, 196865				; 00030101H
	jne	SHORT $LN55@SzDecode2
	test	ecx, ecx
	je	$LN56@SzDecode2
$LN55@SzDecode2:

; 202  :       }
; 203  :     }
; 204  :     else if (coder->MethodID == k_BCJ)

	cmp	edi, 50528515				; 03030103H
	jne	SHORT $LN57@SzDecode2
	test	ecx, ecx
	jne	SHORT $LN57@SzDecode2

; 205  :     {
; 206  :       UInt32 state;
; 207  :       if (ci != 1)

	cmp	eax, 1
	jne	$LN21@SzDecode2

; 208  :         return SZ_ERROR_UNSUPPORTED;
; 209  :       x86_Convert_Init(state);
; 210  :       x86_Convert(outBuffer, outSize, 0, &state, 0);

	mov	eax, DWORD PTR _outSize$GSCopy$[ebp]
	push	ecx
	lea	edx, DWORD PTR _state$80370[ebp]
	push	edx
	push	ecx
	mov	DWORD PTR _state$80370[ebp], ecx
	mov	ecx, DWORD PTR _outBuffer$GSCopy$[ebp]
	push	eax
	push	ecx
	call	_x86_Convert
	add	esp, 20					; 00000014H
	jmp	$LN30@SzDecode2
$LN57@SzDecode2:

; 211  :     }
; 212  :     else if (coder->MethodID == k_BCJ2)

	cmp	edi, 50528539				; 0303011bH
	jne	$LN21@SzDecode2
	test	ecx, ecx
	jne	$LN21@SzDecode2

; 213  :     {
; 214  :       UInt64 offset = GetSum(packSizes, 1);

	mov	esi, DWORD PTR _packSizes$GSCopy$[ebp]
	push	1
	push	esi
	call	_GetSum

; 215  :       UInt64 s3Size = packSizes[1];

	mov	edi, DWORD PTR [esi+8]
	mov	esi, DWORD PTR [esi+12]
	add	esp, 8

; 216  :       SRes res;
; 217  :       if (ci != 3)

	cmp	DWORD PTR _ci$[ebp], 3
	jne	$LN21@SzDecode2

; 218  :         return SZ_ERROR_UNSUPPORTED;
; 219  :       RINOK(LookInStream_SeekTo(inStream, startPos + offset));

	add	eax, DWORD PTR _startPos$[ebp]
	mov	ebx, DWORD PTR _inStream$GSCopy$[ebp]
	adc	edx, DWORD PTR _startPos$[ebp+4]
	push	edx
	push	eax
	push	ebx
	call	_LookInStream_SeekTo
	add	esp, 12					; 0000000cH
	test	eax, eax
	jne	$LN58@SzDecode2

; 220  :       tempSizes[2] = (SizeT)s3Size;
; 221  :       if (tempSizes[2] != s3Size)

	cmp	edi, edi
	jne	$LN44@SzDecode2
	cmp	eax, esi
	jne	$LN44@SzDecode2

; 222  :         return SZ_ERROR_MEM;
; 223  :       tempBuf[2] = (Byte *)IAlloc_Alloc(allocMain, tempSizes[2]);

	mov	eax, DWORD PTR _allocMain$GSCopy$[ebp]
	mov	edx, DWORD PTR [eax]
	push	edi
	push	eax
	call	edx
	mov	ecx, DWORD PTR _tempBuf$GSCopy$[ebp]
	add	esp, 8
	mov	DWORD PTR [ecx+8], eax

; 224  :       if (tempBuf[2] == 0 && tempSizes[2] != 0)

	test	eax, eax
	jne	SHORT $LN4@SzDecode2
	test	edi, edi
	jne	$LN44@SzDecode2
$LN4@SzDecode2:

; 225  :         return SZ_ERROR_MEM;
; 226  :       res = SzDecodeCopy(s3Size, inStream, tempBuf[2]);

	push	eax
	push	esi
	push	edi
	mov	esi, ebx
	call	_SzDecodeCopy
	add	esp, 12					; 0000000cH

; 227  :       RINOK(res)

	test	eax, eax
	jne	$LN58@SzDecode2

; 228  : 
; 229  :       res = Bcj2_Decode(
; 230  :           tempBuf3, tempSize3,
; 231  :           tempBuf[0], tempSizes[0],
; 232  :           tempBuf[1], tempSizes[1],
; 233  :           tempBuf[2], tempSizes[2],
; 234  :           outBuffer, outSize);

	mov	edx, DWORD PTR _outSize$GSCopy$[ebp]
	mov	eax, DWORD PTR _outBuffer$GSCopy$[ebp]
	push	edx
	mov	edx, DWORD PTR _tempSizes$[ebp+4]
	push	eax
	mov	eax, DWORD PTR _tempBuf$GSCopy$[ebp]
	mov	ecx, DWORD PTR [eax+8]
	push	edi
	push	ecx
	mov	ecx, DWORD PTR [eax+4]
	mov	eax, DWORD PTR [eax]
	push	edx
	mov	edx, DWORD PTR _tempSizes$[ebp]
	push	ecx
	mov	ecx, DWORD PTR _tempSize3$[ebp]
	push	edx
	mov	edx, DWORD PTR _tempBuf3$[ebp]
	push	eax
	push	ecx
	push	edx
	call	_Bcj2_Decode
	add	esp, 40					; 00000028H

; 235  :       RINOK(res)
; 236  :     }
; 237  :     else

	jmp	$LN62@SzDecode2
$LN56@SzDecode2:

; 156  :     {
; 157  :       UInt32 si = 0;
; 158  :       UInt64 offset;
; 159  :       UInt64 inSize;
; 160  :       Byte *outBufCur = outBuffer;
; 161  :       SizeT outSizeCur = outSize;

	mov	ecx, DWORD PTR _outSize$GSCopy$[ebp]
	mov	ebx, DWORD PTR _outBuffer$GSCopy$[ebp]
	xor	edi, edi
	mov	DWORD PTR _outSizeCur$80343[ebp], ecx

; 162  :       if (folder->NumCoders == 4)

	cmp	edx, 4
	jne	$LN19@SzDecode2

; 163  :       {
; 164  :         UInt32 indices[] = { 3, 2, 0 };
; 165  :         UInt64 unpackSize = folder->UnpackSizes[ci];

	mov	ecx, DWORD PTR [esi+12]
	mov	esi, DWORD PTR [ecx+eax*8]
	mov	ecx, DWORD PTR [ecx+eax*8+4]

; 166  :         si = indices[ci];

	lea	ebx, DWORD PTR [eax*4]
	mov	DWORD PTR _indices$80345[ebp], 3
	mov	DWORD PTR _indices$80345[ebp+4], 2
	mov	DWORD PTR _indices$80345[ebp+8], edi
	mov	edi, DWORD PTR _indices$80345[ebp+ebx]

; 167  :         if (ci < 2)

	cmp	eax, 2
	jae	SHORT $LN60@SzDecode2

; 168  :         {
; 169  :           Byte *temp;
; 170  :           outSizeCur = (SizeT)unpackSize;
; 171  :           if (outSizeCur != unpackSize)

	xor	eax, eax
	mov	DWORD PTR _outSizeCur$80343[ebp], esi
	cmp	esi, esi
	jne	$LN44@SzDecode2
	cmp	eax, ecx
	jne	$LN44@SzDecode2

; 172  :             return SZ_ERROR_MEM;
; 173  :           temp = (Byte *)IAlloc_Alloc(allocMain, outSizeCur);

	mov	eax, DWORD PTR _allocMain$GSCopy$[ebp]
	mov	edx, DWORD PTR [eax]
	push	esi
	push	eax
	call	edx
	add	esp, 8

; 174  :           if (temp == 0 && outSizeCur != 0)

	test	eax, eax
	jne	SHORT $LN23@SzDecode2
	test	esi, esi
	jne	$LN44@SzDecode2
$LN23@SzDecode2:

; 176  :           outBufCur = tempBuf[1 - ci] = temp;

	mov	edx, DWORD PTR _tempBuf$GSCopy$[ebp]
	mov	ecx, ebx
	neg	ecx
	mov	DWORD PTR [ecx+edx+4], eax
	mov	ebx, eax

; 177  :           tempSizes[1 - ci] = outSizeCur;

	mov	DWORD PTR _tempSizes$[ebp+ecx+4], esi
	jmp	SHORT $LN19@SzDecode2
$LN60@SzDecode2:

; 178  :         }
; 179  :         else if (ci == 2)

	jne	$LN21@SzDecode2

; 180  :         {
; 181  :           if (unpackSize > outSize) /* check it */

	xor	eax, eax
	cmp	ecx, eax
	ja	$LN45@SzDecode2
	jb	SHORT $LN54@SzDecode2
	cmp	esi, DWORD PTR _outSize$GSCopy$[ebp]
	ja	$LN45@SzDecode2
$LN54@SzDecode2:

; 183  :           tempBuf3 = outBufCur = outBuffer + (outSize - (size_t)unpackSize);

	mov	ebx, DWORD PTR _outSize$GSCopy$[ebp]
	sub	ebx, esi
	add	ebx, DWORD PTR _outBuffer$GSCopy$[ebp]

; 184  :           tempSize3 = outSizeCur = (SizeT)unpackSize;

	mov	DWORD PTR _outSizeCur$80343[ebp], esi
	mov	DWORD PTR _tempBuf3$[ebp], ebx
	mov	DWORD PTR _tempSize3$[ebp], esi
$LN19@SzDecode2:

; 188  :       }
; 189  :       offset = GetSum(packSizes, si);

	mov	esi, DWORD PTR _packSizes$GSCopy$[ebp]
	push	edi
	push	esi
	call	_GetSum

; 190  :       inSize = packSizes[si];
; 191  :       RINOK(LookInStream_SeekTo(inStream, startPos + offset));

	add	eax, DWORD PTR _startPos$[ebp]
	mov	ecx, DWORD PTR _packSizes$GSCopy$[ebp]
	adc	edx, DWORD PTR _startPos$[ebp+4]
	mov	esi, DWORD PTR [esi+edi*8]
	mov	edi, DWORD PTR [ecx+edi*8+4]
	push	edx
	mov	edx, DWORD PTR _inStream$GSCopy$[ebp]
	push	eax
	push	edx
	call	_LookInStream_SeekTo
	add	esp, 20					; 00000014H
	test	eax, eax
	jne	$LN58@SzDecode2

; 192  : 
; 193  :       if (coder->MethodID == k_Copy)

	mov	eax, DWORD PTR _coder$80336[ebp]
	mov	ecx, DWORD PTR [eax+8]
	or	ecx, DWORD PTR [eax+12]
	jne	SHORT $LN17@SzDecode2

; 194  :       {
; 195  :         if (inSize != outSizeCur) /* check it */

	xor	eax, eax
	cmp	esi, DWORD PTR _outSizeCur$80343[ebp]
	jne	$LN47@SzDecode2
	cmp	edi, eax
	jne	$LN47@SzDecode2

; 196  :           return SZ_ERROR_DATA;
; 197  :         RINOK(SzDecodeCopy(inSize, inStream, outBufCur));

	push	ebx
	push	edi
	push	esi
	mov	esi, DWORD PTR _inStream$GSCopy$[ebp]
	call	_SzDecodeCopy
	add	esp, 12					; 0000000cH

; 198  :       }
; 199  :       else

	jmp	SHORT $LN62@SzDecode2
$LN17@SzDecode2:

; 200  :       {
; 201  :         RINOK(SzDecodeLzma(coder, inSize, inStream, outBufCur, outSizeCur, allocMain));

	mov	edx, DWORD PTR _outSizeCur$80343[ebp]
	mov	ecx, DWORD PTR _allocMain$GSCopy$[ebp]
	push	edx
	push	edi
	push	esi
	mov	edx, ebx
	mov	ebx, DWORD PTR _inStream$GSCopy$[ebp]
	push	eax
	call	_SzDecodeLzma
	add	esp, 16					; 00000010H
$LN62@SzDecode2:
	test	eax, eax
	jne	$LN58@SzDecode2
	mov	esi, DWORD PTR _folder$GSCopy$[ebp]
$LN30@SzDecode2:

; 144  :   UInt32 ci;
; 145  :   SizeT tempSizes[3] = { 0, 0, 0};
; 146  :   SizeT tempSize3 = 0;
; 147  :   Byte *tempBuf3 = 0;
; 148  : 
; 149  :   RINOK(CheckSupportedFolder(folder));
; 150  : 
; 151  :   for (ci = 0; ci < folder->NumCoders; ci++)

	mov	eax, DWORD PTR _ci$[ebp]
	mov	edx, DWORD PTR [esi+16]
	inc	eax
	mov	DWORD PTR _ci$[ebp], eax
	cmp	eax, edx
	jb	$LL53@SzDecode2

; 238  :       return SZ_ERROR_UNSUPPORTED;
; 239  :   }
; 240  :   return SZ_OK;

	pop	ebx
	pop	edi
	xor	eax, eax
	pop	esi

; 241  : }

	mov	ecx, DWORD PTR __$ArrayPad$[ebp]
	xor	ecx, ebp
	call	@__security_check_cookie@4
	mov	esp, ebp
	pop	ebp
	ret	0
$LN44@SzDecode2:
	pop	ebx
	pop	edi

; 175  :             return SZ_ERROR_MEM;

	mov	eax, 2
	pop	esi

; 241  : }

	mov	ecx, DWORD PTR __$ArrayPad$[ebp]
	xor	ecx, ebp
	call	@__security_check_cookie@4
	mov	esp, ebp
	pop	ebp
	ret	0
$LN45@SzDecode2:
	pop	ebx
	pop	edi

; 182  :             return SZ_ERROR_PARAM;

	mov	eax, 5
	pop	esi

; 241  : }

	mov	ecx, DWORD PTR __$ArrayPad$[ebp]
	xor	ecx, ebp
	call	@__security_check_cookie@4
	mov	esp, ebp
	pop	ebp
	ret	0
$LN21@SzDecode2:
	pop	ebx
	pop	edi

; 185  :         }
; 186  :         else
; 187  :           return SZ_ERROR_UNSUPPORTED;

	mov	eax, 4
	pop	esi

; 241  : }

	mov	ecx, DWORD PTR __$ArrayPad$[ebp]
	xor	ecx, ebp
	call	@__security_check_cookie@4
	mov	esp, ebp
	pop	ebp
	ret	0
$LN47@SzDecode2:
	mov	ecx, DWORD PTR __$ArrayPad$[ebp]
	pop	ebx
	pop	edi
	xor	ecx, ebp
	mov	eax, 1
	pop	esi
	call	@__security_check_cookie@4
	mov	esp, ebp
	pop	ebp
	ret	0
_SzDecode2 ENDP
_TEXT	ENDS
PUBLIC	_SzDecode
; Function compile flags: /Ogtp
;	COMDAT _SzDecode
_TEXT	SEGMENT
_tempBuf$ = -12						; size = 12
_packSizes$ = 8						; size = 4
_folder$ = 12						; size = 4
_inStream$ = 16						; size = 4
_startPos$ = 20						; size = 8
_outBuffer$ = 28					; size = 4
_outSize$ = 32						; size = 4
_allocMain$ = 36					; size = 4
_SzDecode PROC						; COMDAT

; 246  : {

	push	ebp
	mov	ebp, esp
	sub	esp, 12					; 0000000cH

; 247  :   Byte *tempBuf[3] = { 0, 0, 0};
; 248  :   int i;
; 249  :   SRes res = SzDecode2(packSizes, folder, inStream, startPos,
; 250  :       outBuffer, (SizeT)outSize, allocMain, tempBuf);

	mov	ecx, DWORD PTR _outSize$[ebp]
	mov	edx, DWORD PTR _outBuffer$[ebp]
	push	ebx
	push	esi
	push	edi
	mov	edi, DWORD PTR _allocMain$[ebp]
	lea	eax, DWORD PTR _tempBuf$[ebp]
	push	eax
	mov	eax, DWORD PTR _startPos$[ebp+4]
	push	edi
	push	ecx
	mov	ecx, DWORD PTR _startPos$[ebp]
	push	edx
	mov	edx, DWORD PTR _inStream$[ebp]
	push	eax
	mov	eax, DWORD PTR _folder$[ebp]
	push	ecx
	mov	ecx, DWORD PTR _packSizes$[ebp]
	push	edx
	xor	esi, esi
	push	eax
	push	ecx
	mov	DWORD PTR _tempBuf$[ebp], esi
	mov	DWORD PTR _tempBuf$[ebp+4], esi
	mov	DWORD PTR _tempBuf$[ebp+8], esi
	call	_SzDecode2
	add	esp, 36					; 00000024H
	mov	ebx, eax
$LL3@SzDecode:

; 251  :   for (i = 0; i < 3; i++)
; 252  :     IAlloc_Free(allocMain, tempBuf[i]);

	mov	edx, DWORD PTR _tempBuf$[ebp+esi*4]
	mov	eax, DWORD PTR [edi+4]
	push	edx
	push	edi
	call	eax
	inc	esi
	add	esp, 8
	cmp	esi, 3
	jl	SHORT $LL3@SzDecode

; 253  :   return res;

	pop	edi
	pop	esi
	mov	eax, ebx
	pop	ebx

; 254  : }

	mov	esp, ebp
	pop	ebp
	ret	0
_SzDecode ENDP
_TEXT	ENDS
END
