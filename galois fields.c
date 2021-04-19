//author - shivankthakur
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(void)
{
	//READING INPUT
	char fx[15],gx[15],mx[15];
	scanf("%s",fx);
	scanf("%s",gx);
	scanf("%s",mx);
	int fx_deg = strlen(fx);	//actuallly "degree" of polynomial is strlen() - 1 but ok :P
	int gx_deg = strlen(gx);
	int mx_deg = strlen(mx);
	int fx_coeff[fx_deg];
	int gx_coeff[gx_deg];
	int mx_coeff[mx_deg];
	//printf("\n");

	//copying all polynomials string inputs into arrays

	for (int i = fx_deg - 1, j = 0; i >= 0; --i, ++j)
	{
		if(fx[i] == '1')
			fx_coeff[j] = 1;
		else
			fx_coeff[j] = 0;
		//printf("%d",fx_coeff[j]);
	}
	//printf("\n");
	for (int i = gx_deg - 1, j = 0; i >= 0; --i, ++j)
	{
		if(gx[i] == '1')
			gx_coeff[j] = 1;
		else
			gx_coeff[j] = 0;
		//printf("%d",gx_coeff[j]);
	}
	//printf("\n");
	for (int i = mx_deg - 1, j = 0; i >= 0; --i, ++j)
	{
		if(mx[i] == '1')
			mx_coeff[j] = 1;
		else
			mx_coeff[j] = 0;
		//printf("%d",mx_coeff[j]);
	}
	//printf("\n");

	//ALGO

	//OPERATION
	//mul = fx*gx
	int size = fx_deg + gx_deg;
	int mul[size];
	memset(mul, 0, sizeof(mul));
	for (int i = 0; i < fx_deg; ++i)
	{
		for (int j = 0; j < gx_deg; ++j)
		{
			if(fx_coeff[i] && gx_coeff[j])
				mul[i+j]++;
		}
	}
	for (int i = 0; i < size; ++i)
	{
		mul[i] = mul[i]%2;
		//printf("%d ",mul[i]);
	}

	//OPERATION 
	//(mul)mod(mx)
	//here instead of subtracting at every step i'll rather at the end do a (mod2) and eliminate all the even coeff terms.
	//m(x)	)	mul    (	quotient
	//			rem

	//getting divisor highest power
	int mx_hi;
	for (int i = mx_deg-1; i >= 0; --i)
	{
		if(mx_coeff[i] == 1)
		{
			mx_hi = i;
			break;
		}
	}
	//printf("mx_hi = %d\n", mx_hi);

	//getting dividend highest power
	int mul_hi;
	for (int i = size-1; i >= 0; --i)
	{
		if(mul[i] == 1)
		{
			mul_hi = i;
			break;
		}
	}
	//printf("mul_hi = %d\n", mul_hi);

	int rem[size];
	int mx2[size];
	//memset(rem,0,sizeof(rem));
	memset(mx2,0,sizeof(mx2));

	//initializing rem as dividend to be able to use dynamically from the first time itself
	for (int i = 0; i < size; ++i)
	{
		rem[i] = mul[i];
	}
	int rem_hi = mul_hi;

	//THE LONG DIVISION
	int q_hi;
	while(rem_hi >= mx_hi)
	{

		//finding and multiplying quotient with divisor
		memset(mx2,0,sizeof(mx2));
		q_hi = rem_hi - mx_hi;
		for (int i = 0; i < mx_deg; ++i)
		{
			if(mx_coeff[i] == 1)
			{
				mx2[i+ q_hi]++;
			}
		}

		//getting tmp remainder after "subtration"
		for (int i = 0; i < size; ++i)
		{
			if(mx2[i] == 1)
			{
				rem[i]++;
				rem[i] = rem[i]%2;	//the actual "subtraction" of common terms
			}
		}

		//getting/updating remainder highest power
		for (int i = size-1; i >= 0; --i)
		{
			if(rem[i] == 1)
			{
				rem_hi = i;
				break;
			}
		}
	//	printf("rem_hi = %d\n", rem_hi);
	}

	/*
	//printing final remainder as an array
	for (int i = 0; i < size; ++i)
	{
		printf("%d",rem[i]);
	}*/

	//converting array to string??[have to reverse for final answer!!! bcos final answer power of x increases from right to left]
	char ans[rem_hi+2];
	ans[rem_hi+1] = '\0';
	int j = 0;
	for (int i = rem_hi; i >=0 ; --i)
	{
		if(rem[i] == 1)
			ans[j] = '1';
		else
			ans[j] = '0';
		j++;
	}

	//PRINTING FINAL ANSWER :D
	printf("%s",ans);
}