


const int abcd[]=
{
	//Codigo ascii  '0' = 48						  Char		PI		PF		ID
	62	,	69	,	73	,	81	,	62	,	0	,	//	0	De	0	-	5 		0
	17	,	33	,	127	,	1	,	1	,	0	,	//	1	De	6	-	11 		1
	33	,	67	,	69	,	73	,	49	,	0	,	//	2	De	12	-	17 		2
	34	,	65	,	73	,	73	,	54	,	0	,	//	3	De	18	-	23 		3
	12	,	20	,	36	,	127	,	4	,	0	,	//	4	De	24	-	29 		4
	114	,	81	,	81	,	81	,	78	,	0	,	//	5	De	30	-	35 		5
	62	,	73	,	73	,	73	,	38	,	0	,	//	6	De	36	-	41 		6
	64	,	71	,	72	,	80	,	96	,	0	,	//	7	De	42	-	47 		7
	54	,	73	,	73	,	73	,	54	,	0	,	//	8	De	48	-	53 		8
	50	,	73	,	73	,	73	,	62	,	0	,	//	9	De	54	-	59 		9
	//10 elementos de 0 a 59
	//Codigo ascii  'A' = 65
	31	,	36	,	68	,	68	,	127	,	0	,	//	A	De	60	-	65 		10
	127	,	73	,	73	,	73	,	54	,	0	,	//	B	De	66	-	71 		11
	62	,	65	,	65	,	65	,	34	,	0	,	//	C	De	72	-	77 		12
	127	,	65	,	65	,	65	,	62	,	0	,	//	D	De	78	-	83 		13
	127	,	73	,	73	,	73	,	65	,	0	,	//	E	De	84	-	89 		14
	127	,	72	,	72	,	72	,	64	,	0	,	//	F	De	90	-	95 		15
	62	,	65	,	65	,	69	,	38	,	0	,	//	G	De	96	-	101 	16
	127	,	8	,	8	,	8	,	127	,	0	,	//	H	De	102	-	107 	17
	0	,	65	,	127	,	65	,	0	,	0	,	//	I	De	108	-	113 	18
	0	,	2	,	65	,	65	,	126	,	0	,	//	J	De	114	-	119 	19
	127	,	8	,	20	,	34	,	65	,	0	,	//	K	De	120	-	125 	20
	127	,	1	,	1	,	1	,	1	,	0	,	//	L	De	126	-	131 	21
	127	,	32	,	24	,	32	,	127	,	0	,	//	M	De	132	-	137 	22
	127	,	16	,	8	,	4	,	127	,	0	,	//	N	De	138	-	143 	23
	62	,	65	,	65	,	65	,	62	,	0	,	//	O	De	144	-	149 	24
	127	,	72	,	72	,	72	,	48	,	0	,	//	P	De	150	-	155 	25
	60	,	66	,	66	,	66	,	61	,	0	,	//	Q	De	156	-	161 	26
	127	,	72	,	76	,	74	,	49	,	0	,	//	R	De	162	-	167 	27
	50	,	73	,	73	,	73	,	38	,	0	,	//	S	De	168	-	173 	28
	64	,	64	,	127	,	64	,	64	,	0	,	//	T	De	174	-	179 	29
	126	,	1	,	1	,	1	,	126	,	0	,	//	U	De	180	-	185 	30
	124	,	2	,	1	,	2	,	124	,	0	,	//	V	De	186	-	191 	31
	126	,	1	,	6	,	1	,	126	,	0	,	//	W	De	192	-	197 	32
	99	,	20	,	8	,	20	,	99	,	0	,	//	X	De	198	-	203 	33
	114	,	9	,	9	,	9	,	126	,	0	,	//	Y	De	204	-	209 	34
	67	,	69	,	73	,	81	,	97	,	0	,	//	Z	De	210	-	215 	35
	//26 elementos de 60 a 215
	//Codigo ascii  'a' = 97
	6	,	21	,	21	,	21	,	15	,	0	,	//	a	De	216	-	221 	36
	63	,	9	,	9	,	9	,	6	,	0	,	//	b	De	222	-	227 	37
	14	,	17	,	17	,	17	,	9	,	0	,	//	c	De	228	-	233 	38
	6	,	9	,	9	,	9	,	63	,	0	,	//	d	De	234	-	239 	39
	14	,	21	,	21	,	21	,	13	,	0	,	//	e	De	240	-	245 	40
	8	,	31	,	40	,	40	,	0	,	0	,	//	f	De	246	-	251 	41
	25	,	37	,	37	,	37	,	62	,	0	,	//	g	De	252	-	257		42
	63	,	8	,	8	,	8	,	7	,	0	,	//	h	De	258	-	263 	43
	0	,	9	,	47	,	1	,	0	,	0	,	//	i	De	264	-	269 	44
	2	,	1	,	1	,	1	,	94	,	0	,	//	j	De	270	-	275 	45
	63	,	4	,	10	,	17	,	0	,	0	,	//	k	De	276	-	281 	46
	62	,	1	,	1	,	1	,	0	,	0	,	//	l	De	282	-	287 	47
	31	,	16	,	15	,	16	,	31	,	0	,	//	m	De	288	-	293 	48
	31	,	16	,	16	,	15	,	0	,	0	,	//	n	De	294	-	299 	49
	14	,	17	,	17	,	17	,	14	,	0	,	//	o	De	300	-	305 	50
	63	,	36	,	36	,	36	,	24	,	0	,	//	p	De	306	-	311 	51
	24	,	36	,	36	,	36	,	63	,	0	,	//	q	De	312	-	317 	52
	0	,	15	,	16	,	16	,	0	,	0	,	//	r	De	318	-	323 	53
	9	,	21	,	21	,	21	,	18	,	0	,	//	s	De	324	-	329 	54
	16	,	16	,	62	,	17	,	17	,	0	,	//	t	De	330	-	335 	55
	30	,	1	,	1	,	2	,	31	,	0	,	//	u	De	336	-	341 	56
	0	,	30	,	1	,	1	,	30	,	0	,	//	v	De	342	-	347 	57
	30	,	1	,	14	,	1	,	30	,	0	,	//	w	De	348	-	353 	58
	17	,	10	,	4	,	10	,	17	,	0	,	//	x	De	354	-	359 	59
	57	,	5	,	5	,	5	,	62	,	0	,	//	y	De	360	-	365 	60
	17	,	19	,	21	,	25	,	17	,	0	,	//	z	De	366	-	371 	61
	//26 elementos de 216 a 371
	//Codigo ascii  ' ' = 32
    0   ,  0  	,  	0  	,  	0  	,  	0  	,  	0  	,	// Espacio De 372 - 377 	62
   //1 elemento de 272 a 377 
};