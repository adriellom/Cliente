/*-------------------------------------------------------------------*
 * Filtro_IIR.h                                                      *
 * Historico:	25/05/22	Primera version                          *
 * Autor: Lombardo Leandro Adriel                                    *
 *                                                                   *
 *-------------------------------------------------------------------*/

//Variable de PI
#define pi 3.1415

// Definicion de estructura 
typedef struct {
	float  Vi;
	float  Vo_prev;
	float  Vo;
	float  Fc;
	float  Fs;
} IIR_1order;

// Prototipo de funciones utilizadas
void IIR_1order_init(IIR_1order* v, float fc);
float IIR_1order_FUNC(IIR_1order* v);