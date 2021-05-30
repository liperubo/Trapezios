// ------------------------- Cabeçalho --------------------------- //
/*Projeto Método dos Multiplos Quadrados - Métodos Númericos

Integrantes:
Felipe Eler de Oliveira Machado 200738
Felipe Victorino Sarubo 200574

Turma: CP004TIM2*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ------------------------- Estruturas --------------------------- //

typedef struct TRAP
{
	float x;
  float fx;
} TRAP;

// ------------------------- Protótipos de Funções ---------------- //

void alocaTRAP(TRAP **p, int tam);
void alocaInt(int **p, int m);
void input(float *a, float *b, int *n);
float substitui(int *p, int exp, float V);

// ------------------------- Main --------------------------------- //

int main()
{
  char dnv = 's';
  // ----- Passo 1. Input  -----
  int *pFunc= NULL;
  
  float A, B, H, I;
  int i, N, exp;  

  do
  {
    
    
    // Receber a Func (Função):
    //   Receber o maior Exp (Expoente)
    printf("\nDigite o maior expoente: ");
    scanf("%i",&exp);
    fflush(stdin);

    alocaInt(&pFunc, exp+1);

    //   Loop (For):
    //     Receber os Coeficientes em ordem decrescente
    for (i = exp; i >= 0; i--)
    {
      if (i == 0){printf("Digite o valor independente: ");}
      else if (i == 1){printf("Digite o valor que acompanha x: ");}
      else{printf("Digite o valor que acompanha x^%i: ", i);}
      
      scanf("%i",(pFunc + i));
      fflush(stdin);
    }

    do{
      TRAP *pTRAP = NULL;
      input(&A, &B, &N);

      // ----- Passo 2. Calculo ----- 
      // Alocar Dinamicamente N+1 estruturas TRAP
      alocaTRAP(&pTRAP, N+1);
      
      // Definir H (Tamanho do Trapézio)
        // H = (B - A) / N
      H = (B - A) / N;
      // Definir I (Integral)
        // I = 0
      I = 0;
      // Loop(For i<=N):
      printf("\nx\tfx");
      for (i = 0; i <= N; i++)
      {
        // x[i] = A + (i * H)
        (pTRAP+i)->x = A + (i * H);
        // fx[i] = f(x[i])
        (pTRAP+i)->fx = substitui(pFunc, exp, (pTRAP+i)->x);

        printf("\n%.4f\t%.4f",(pTRAP+i)->x,(pTRAP+i)->fx);

        // Se i = 0 ou i = N
        if (i == 0 || i == N)
        {
          // I += modulo(H/2 * fx[i])
          I += fabs(H/2 * (pTRAP+i)->fx);
        }  
        // Se i != 0 ou i != N
        if (i > 0 && i < N)
        {
          // I += modulo(H * fx[i])
          I += fabs(H * (pTRAP+i)->fx);
        }
      }

      // ----- Passo 3. Output" ----- 
      printf("\n\n ITR = %.4f", I);

      do
      {
        printf("\n\nDeseja calcular com outra quantidade de trapezios? [s/n]: ");
        scanf("%c", &dnv);
        fflush(stdin);
      } while (dnv != 's' && dnv != 'S' && dnv != 'n' && dnv != 'N');
      system("CLS");
    }while (dnv == 's' || dnv == 'S');
    do
    {
      printf("\n\nDeseja calcular com outra funcao? [s/n]: ");
      scanf("%c", &dnv);
      fflush(stdin);
    } while (dnv != 's' && dnv != 'S' && dnv != 'n' && dnv != 'N');
    system("CLS");
  } while (dnv == 's' || dnv == 'S');
  printf("\n\n");
  return 0;
}

// ------------------------- Funções ------------------------------ //

void alocaTRAP(TRAP **p, int m)
{
  if ((*p = (TRAP *)realloc(*p, m * sizeof(TRAP))) == NULL)
  {
    printf("\nErro na alocacao. O programa sera encerrado!");
    exit(1);
  }
}

void alocaInt(int **p, int m){
	if((*p = (int*)realloc(*p, m * sizeof(int))) == NULL)
	{
		printf("\nErro na alocacao. O programa sera encerrado!");
		exit(1);
	}
}

void input(float *a, float *b, int *n){
	// Receber A e B (Limites)
	printf("Digite primeiro o limite (A): ");
	scanf("%f", a);
	fflush(stdin);

	printf("Digite segundo o limite (B): ");
	scanf("%f", b);
	fflush(stdin);

  // Receber N (Quantidade de Trapézios)
  printf("Digite a quantidade de trapezios (N): ");
	scanf("%i", n);
	fflush(stdin);
}

float substitui(int *p, int exp, float V){
	int i = 0;
	float result = 0.0f;
	for (i = exp; i >= 0; i--)
	{
		result += *(p + i) * powf(V, i);
	}
	return result;
}

// ------------------------- To Do List --------------------------- //
/*
Processamento:
  "Passo 0. Setup"
    Definir Estruturas
      TRAP (Trapézios)
        float x
        float fx
    Definir Funções
      substitui()

  "Passo 1. Input"
    Receber a Func (Função):
      Receber o maior Exp (Expoente)
      Loop (For):
        Receber os Coeficientes em ordem decrescente
    Receber A e B (Limites)
    Receber N (Quantidade de Trapézios)

  "Passo 2. Calculo"
    Alocar Dinamicamente N+1 estruturas TRAP
    Definir H (Tamanho do Trapézio)
      H = (B - A) / N
    Definir I (Integral)
      I = 0
    Loop(For i<=N):
      x[i] = A + (i * H)
      fx[i] = f(x[i])

      Se i = 0 ou i = N
        I += modulo(H/2 * fx[i])
      Se i != 0 ou i != N
        I += modulo(H * fx[i])

  "Passo 3. Output"
    "I"
*/