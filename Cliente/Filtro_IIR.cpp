#include "Filtro_IIR.h"
/*-------------------------------------------------------------------*
 * IIR_1order_init()                                                 *
 *                                                                   *
 * Entrada:     fc                                                   *
 *                                                                   *
 * Salida:      No posee                                             *
 *                                                                   *
 * Retorno:     No posee                                             *
 *                                                                   *
 * Descripcion: Inicializa las variables del filtro                  *
 *-------------------------------------------------------------------*/

void IIR_1order_init(IIR_1order* v, float fc)
{
	v->Vi = 0;
	v->Vo_prev = 0;
	v->Vo = 0;

	//frecuencia de corte low pass	
	v->Fc = fc;

	// execute 1000 every second
	v->Fs = 100;
}

/*-------------------------------------------------------------------*
 * IIR_1order_FUNC()                                                 *
 *                                                                   *
 * Entrada:     fc                                                   *
 *                                                                   *
 * Salida:      No posee                                             *
 *                                                                   *
 * Retorno:     No posee                                             *
 *                                                                   *
 * Descripcion: funcion para calcular la señal de salida del filtro  *
 *-------------------------------------------------------------------*/
float IIR_1order_FUNC(IIR_1order* v)
{
	float RC, Cof1, Cof2;

	RC = (float)(1.0 / 2.0 / pi / v->Fc);
	Cof1 = 1 / (1 + RC * v->Fs);
	Cof2 = RC * v->Fs / (1 + RC * v->Fs);

	v->Vo = Cof1 * v->Vi + Cof2 * v->Vo_prev;

	v->Vo_prev = v->Vo;

	return v->Vo;
}
