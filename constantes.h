#ifndef CONSTANTES_H
#define CONSTANTES_H

//------------------------------------------------------------------------------------------------------
// MACROS DE ERRO
//------------------------------------------------------------------------------------------------------

typedef enum
{
   OK,										/* 0 */
   NUMERO_MAXIMO_NOS_ULTRAPASSADO,			/* 1 */
   SISTEMA_SINGULAR,						/* 2 */
   NUMERO_MAXIMO_ELEMENTOS_ULTRAPASSADO,	/* 3 */
   ELEMENTO_DESCONHECIDO,					/* 4 */
   FONTE_DESCONHECIDA,						/* 5 */
   OPCAO_DESCONHECIDA,						/* 6 */
   ERRO_ARQUIVO_INEXISTENTE,				/* 7 */
   ERRO_CRIACAO_ARQUIVO,					/* 8 */
   ERRO_DIVISAO_POR_ZERO,					/* 9 */
   ERRO_ABRINDO_ARQUIVO_ESCRITA,    		/* 10 */
   NUMERO_ARGUMENTOS_INVALIDOS,				/* 11 */
   ERRO_DIVISAO_COMPLEXO					/* 12 */
} MacrosDeErro;

//------------------------------------------------------------------------------------------------------


#endif */// CONSTANTES_H
