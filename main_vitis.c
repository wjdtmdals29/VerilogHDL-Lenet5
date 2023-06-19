/*******************************************************************************
Author: joohan.kim (https://blog.naver.com/chacagea)
Associated Filename: main.c
Purpose: LENET Core test (Demo)
Revision History: March 08, 2020 - initial release
*******************************************************************************/

#include <stdio.h>
#include "xil_printf.h"
#include "xil_types.h"
#include "xparameters.h"
#include "xil_io.h"
#include "xil_exception.h"
#include "xtime_l.h"
#include <stdlib.h>
#include <time.h>
#define max(x, y) (x) > (y) ? (x) : (y)

#define ksize 5

#define ich1 1
#define och1 4
#define ichsize1 28
#define ochsize1 ichsize1-ksize+1
#define bwtrunc1 20-16

#define ich2 och1
#define och2 12
#define ichsize2 (ochsize1)/2
#define ochsize2 ichsize2-ksize+1
#define bwtrunc2 27-16

#define ich3 och2*ichsize3*ichsize3
#define ichsize3 (ochsize2)/2
#define bwtruncfc 30-16
#define och3 10

#define LENET_CE_ADDR 				0x00
#define LENET_FMAP_ADDR 			0x04
#define LENET_WEIGHT_ADDR 	0x08
#define LENET_FC_BIAS_ADDR 			0x20

#define LENET_RESULT_EN_ADDR 		0x24
#define LENET_RESULT_END_ADDR 		0x28
#define LENET_RESULT_ADDR 			0x2C

#define FMAP_SIZE 			784
#define CONV1_WEIGHT_SIZE	100
#define CONV2_WEIGHT_SIZE 	300
#define FC_WEIGHT_SIZE 		1920
#define FC_BIAS_SIZE		10
static int Max(int a, int b, int c, int d)
{
	int max1 = max(a, b);
	int max2 = max(c, d);
	int max3 = max(max1, max2);
	return max3;
}
static int Max_class(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j)
{
  int result;
	int max1 = max(a, b);
	int max2 = max(c, d);
	int max3 = max(e, f);
  int max4 = max(g, h);
  int max5 = max(i, j);
  int max2_0 = max(max1, max2);
  int max2_1 = max(max3, max4);
  int max3_0 = max(max2_0, max2_1);
  int max_final = max(max3_0, max5);
  if(max_final == a){
    result = 0;
    return result; 
  }
  else if(max_final == b){
    result = 1;
    return result; 
  }
  else if(max_final == c){
    result = 2;
    return result; 
  }
  else if(max_final == d){
    result = 3;
    return result; 
  }
  else if(max_final == e){
    result = 4;
    return result; 
  }
  else if(max_final == f){
    result = 5;
    return result; 
  }
  else if(max_final == g){
    result = 6;
    return result; 
  }
  else if(max_final == h){
    result = 7;
    return result; 
  }
  else if(max_final == i){
    result = 8;
    return result; 
  }
  else if(max_final == j){
    result = 9;
    return result; 
  }
}
static int relu(int x)
{
	if (x > 0) return x;
	return 0;
}


int main()
{
	int inbyte_in;
	int val;
	signed int i, m, n, p, q, j, b;
	signed int out1[och1][ochsize1][ochsize1];
	signed int out1_relu[och1][ochsize1][ochsize1];
	signed int out1_max[och1][(ochsize1) / 2][(ochsize1) / 2];

	signed int out2[och2][ochsize2][ochsize2];
	signed int out2_relu[och2][ochsize2][ochsize2];
	signed int out2_max[och2][(ochsize2) / 2][(ochsize2) / 2];
  signed int fmap1[ich1][ichsize1][ichsize1];
  signed int fmap2[ich2][ichsize2][ichsize2];
  signed int weight1[ich1][och1][ksize][ksize];
  signed int weight1_HW[ich1][och1][ksize][ksize];
  signed int weight2[ich2][och2][ksize][ksize];
  signed int weight2_HW[ich2][och2][ksize][ksize];
  signed int fcmap[ich3];
  signed int weight_fc[och3][ich3];
  signed int weight_fc_HW[och3][ich3];
  signed int bias_fc[och3];
  signed int bias_fc_HW[och3];
  signed int out3[och3];
  signed int out3_relu[och3];

  signed int fmap_HW[FMAP_SIZE];

  FILE *fp_fmap;
  FILE *fp_weight1;
  FILE *fp_weight2;
  FILE *fp_weight2_ch1;
  FILE *fp_weight2_ch2;
  FILE *fp_weight2_ch3;
  FILE *fp_weight2_ch4;
  FILE *fp_weight_fc;
  FILE *fp_bias_fc;

  int result;
	

	signed int out_result;
  signed int out_inference_result;
	signed int result_0_rtl0; 
  signed int result_0_rtl1;
  signed int result_0_rtl2;  

fp_fmap = fopen("SW_test_num9_1.txt", "r");
	for (i = 0; i < ich1; i++) {
		for (m = 0; m < ichsize1; m++) {
			for (n = 0; n < ichsize1; n++) {
        fscanf(fp_fmap,"%d",&fmap1[i][m][n]);
			}
		}
	}
	for (i = 0; i < FMAP_SIZE; i++) {
		fscanf(fp_fmap,"%d",&fmap_HW[FMAP_SIZE]);
	}
fclose(fp_fmap);


fp_weight1 = fopen("SW_conv1_weight.txt", "r");
	for (i = 0; i < ich1; i++) {
		for (p = 0; p < och1; p++) {
			for (m = 0; m < ksize; m++) {
				for (n = 0; n < ksize; n++) {
          fscanf(fp_weight1,"%d",&weight1[i][p][m][n]);
        }
			}
		}
	}
fclose(fp_weight1);
fp_weight2 = fopen("SW_conv2_weight.txt", "r");
	for (i = 0; i < ich2; i++) {
		for (p = 0; p < och2; p++) {
			for (m = 0; m < ksize; m++) {
				for (n = 0; n < ksize; n++) {
          fscanf(fp_weight2,"%d",&weight2[i][p][m][n]);
        }
			}
		}
	}
  fclose(fp_weight2);
	
  fp_weight_fc = fopen("SW_fc_weight.txt", "r");
	for (i = 0; i < och3; i++) {
		for (p = 0; p < ich3; p++) {
      fscanf(fp_weight_fc,"%d",&weight_fc[i][p]);
    }
  }
  fclose(fp_weight_fc);
  fp_bias_fc = fopen("SW_fc_bias.txt", "r");
  for (i = 0; i < och3; i++) {
    fscanf(fp_bias_fc,"%d",&bias_fc[i]);
  }
  fclose(fp_bias_fc);

/////////////////////Initialize Convolution layer1 output values zero/////////////////////
	for (i = 0; i < ich1; i++) {
		for (m = 0; m < ochsize1; m++) {
			for (n = 0; n < ochsize1; n++) {
				for (p = 0; p < ksize; p++) {
					for (q = 0; q < ksize; q++) {
						for (j = 0; j < och1; j++) {
							out1[j][m][n] = 0;
						}
					}
				}
			}
		}
	}
	for (m = 0; m < ochsize1; m++) {
		for (n = 0; n < ochsize1; n++) {
			for (j = 0; j < och1; j++) {
				out1_relu[j][m][n] = 0;
			}
		}
	}
	for (m = 0; m < ochsize1; m = m + 2) {
		for (n = 0; n < ochsize1; n = n + 2) {
			for (j = 0; j < och1; j++) {
				out1_max[j][m / 2][n / 2] = 0;
			}
		}
	}

	/////////////////////Initialize Convolution layer2 output values zero/////////////////////
	for (i = 0; i < ich2; i++) {
		for (m = 0; m < ochsize2; m++) {
			for (n = 0; n < ochsize2; n++) {
				for (p = 0; p < ksize; p++) {
					for (q = 0; q < ksize; q++) {
						for (j = 0; j < och2; j++) {
							out2[j][m][n] = 0;
						}
					}
				}
			}
		}
	}
  for (j = 0; j < och2; j++) {
	  for (m = 0; m < ochsize2; m++) {
		  for (n = 0; n < ochsize2; n++) {
			  out2_relu[j][m][n] = 0;
		  }
	  }
  }
  for (j = 0; j < och2; j++) {
	  for (m = 0; m < ochsize2; m = m + 2) {
		  for (n = 0; n < ochsize2; n = n + 2) {
			  out2_max[j][m / 2][n / 2] = 0;
		  }
	  }
  }
for (i = 0; i < och3; i = i + 1){
    out3[i] = 0;
}
for (i = 0; i < och3; i = i + 1){
  out3_relu[i] = 0;
}
result = 0;
			

	double ref_c_run_time;
	double ref_v_run_time;
	XTime ref_c_run_cycle;
	XTime ref_v_run_cycle;

	while (1)
	{
		print ("********************** Start *********************** \r\n ");
		print ("TeraTerm: Please Set Local Echo Mode. \r\n");
		print ("Press '1' Start Demo \r\n");
		print ("Press '2' to exit \r\n");
		print ("Selection:");
		inbyte_in = inbyte ();
		print ("\r\n");
		print ("\r\n");

		XTime tStart, tEnd;

		switch (inbyte_in)
		{
			case '1': // Show all registers
				printf("==== Lenet5 LENET Core. seed_num %d ====\n",tStart);
				srand(tStart);


				
				
/////////////////// LENET Run in PS /////////////////////////////

				printf("============[REF_C] LENET Run in PS .=============\n");
				XTime_GetTime(&tStart);
				
				////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////  Strat convolution layer 1  ////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////

	/////////////////////  Convolution layer1  /////////////////////
	for (i = 0; i < ich1; i++) {
		for (m = 0; m < ochsize1; m++) {
			for (n = 0; n < ochsize1; n++) {
				for (p = 0; p < ksize; p++) {
					for (q = 0; q < ksize; q++) {
						for (j = 0; j < och1; j++) {
							out1[j][m][n] += (fmap1[i][m + p][n + q] * weight1[i][j][p][q]);
						}
					}
				}
			}
		}
	}
	for (j = 0; j < och1; j++) {
		//printf("\n\nout1 channel%d\n", j);
		for (m = 0; m < ochsize1; m++) {
			//printf("\n");
			for (n = 0; n < ochsize1; n++) {
				//printf("%d ", out1[j][m][n]);
			}
		}
	}
	/////////////////////  relu function  /////////////////////
	for (j = 0; j < och1; j++) {
		//printf("\n\nout1 channel%d relu\n",j);
		for (m = 0; m < ochsize1; m++) {
			//printf("\n");
			for (n = 0; n < ochsize1; n++) {
				out1_relu[j][m][n] = relu(out1[j][m][n]);
				//printf("%d ", out1_relu[j][m][n]);
			}
		}
	}
	/////////////////////  maxpooler  /////////////////////
	for (j = 0; j < och1; j++) {
		//printf("\n\nout1 channel%d max\n", j);
		for (m = 0; m < ochsize1; m = m + 2) {
			//printf("\n");
			for (n = 0; n < ochsize1; n = n + 2) {
				out1_max[j][m / 2][n / 2] = Max(out1_relu[j][m][n], out1_relu[j][m][n + 1], out1_relu[j][m + 1][n], out1_relu[j][m + 1][n + 1]);
				//printf("%d ", out1_max[j][m / 2][n / 2]);
			}
		}
	}
  for (i = 0; i < ich2; i = i + 1) {
    //printf("\n\nout1 channel%d truncate\n", i);
		for (m = 0; m < ichsize2; m = m + 1) {
      //printf("\n");
			for (n = 0; n < ichsize2; n = n + 1) {
        for(b = 0; b < bwtrunc1; b = b + 1) {
          out1_max[i][m][n] = out1_max[i][m][n] - (out1_max[i][m][n]*0.5);
        }
        fmap2[i][m][n] = out1_max[i][m][n];
        //printf("%d ",fmap2[i][m][n]);
      }
    }
  }
	////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////  Strat convolution layer 2  ////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////
	for (i = 0; i < ich2; i++) {
		for (m = 0; m < ochsize2; m++) {
			for (n = 0; n < ochsize2; n++) {
				for (p = 0; p < ksize; p++) {
					for (q = 0; q < ksize; q++) {
						for (j = 0; j < och2; j++) {
							out2[j][m][n] += (fmap2[i][m + p][n + q] * weight2[i][j][p][q]);
						}
					}
				}
			}
		}
	}
	for (j = 0; j < och2; j++) {
		//printf("\n\nout2 channel%d\n", j);
		for (m = 0; m < ochsize2; m++) {
			//printf("\n");
			for (n = 0; n < ochsize2; n++) {
				//printf("%d ", out2[j][m][n]);
			}
		}
	}
	/////////////////////  relu function  /////////////////////
  for (j = 0; j < och2; j++) {
    //printf("\n\nout2 channel%d relu\n",j);
	  for (m = 0; m < ochsize2; m++) {
		  //printf("\n");
		  for (n = 0; n < ochsize2; n++) {
			  out2_relu[j][m][n] = relu(out2[j][m][n]);
			  //printf("%d ", out2_relu[j][m][n]);
		  }
	  }
  }
	/////////////////////  maxpooler  /////////////////////
  for (j = 0; j < och2; j++) {
    //printf("\n\nout2 channel%d max\n",j);
	  for (m = 0; m < ochsize2; m = m + 2) {
		  //printf("\n");
		  for (n = 0; n < ochsize2; n = n + 2) {
			  out2_max[j][m / 2][n / 2] = Max(out2_relu[j][m][n], out2_relu[j][m][n + 1], out2_relu[j][m + 1][n], out2_relu[j][m + 1][n + 1]);
			  //printf("%d ", out2_max[j][m / 2][n / 2]);
		  }
	  }
  }
  for (i = 0; i < och2; i = i + 1) {
    //printf("\n\nout2 channel%d truncate\n", i);
		for (m = 0; m < ichsize3; m = m + 1) {
      //printf("\n");
			for (n = 0; n < ichsize3; n = n + 1) {
        for(b = 0; b < bwtrunc2; b = b + 1) {
          out2_max[i][m][n] = out2_max[i][m][n] - (out2_max[i][m][n]*0.5);
        }
        fcmap[(i*ichsize3*ichsize3)+(m*ichsize3)+n] = out2_max[i][m][n];
        //printf("%d ",fcmap[(i*ichsize3*ichsize3)+(m*ichsize3)+n]);
      }
    }
  }
  //printf("\n");
  for (i = 0; i < och3; i = i + 1){
    //printf("\nout3(fc) channel%d = ", i);
    for (m = 0; m < ich3; m = m + 1) {
      out3[i] = out3[i] + (fcmap[m]*weight_fc[i][m]);
      //printf(" %d : %d ",m,out3[i]);
    }
    out3[i] = out3[i] + bias_fc[i];
    //printf("%d\n",out3[i]);
  }
  for (i = 0; i < och3; i = i + 1){
    //printf("\nout3(fc) channel%d relu = ", i);
    out3_relu[i] = relu(out3[i]);
    for(b = 0; b < bwtruncfc; b = b + 1) {
          out3_relu[i] = out3_relu[i] - (out3_relu[i]*0.5);
        }
    //printf("%d\n",out3_relu[i]);
  }
  result = Max_class(out3_relu[0],out3_relu[1],out3_relu[2],out3_relu[3],
  out3_relu[4],out3_relu[5],out3_relu[6],out3_relu[7],out3_relu[8],out3_relu[9]);


				XTime_GetTime(&tEnd);
				ref_c_run_cycle = 2*(tEnd - tStart);
				ref_c_run_time = 1.0 * (tEnd - tStart) / (COUNTS_PER_SECOND/1000000);
				printf("[REF_C] Output took %llu clock cycles.\n", ref_c_run_cycle);
				printf("[REF_C] Output took %.2f us.\n", ref_c_run_time);
				printf("[REF_C] result : %d\n", result);

/////////////////// LENET Run in PL /////////////////////////////
				printf("============[RTL_V] LENET Run in PL .=============\n");
				for (i = 0 ; i < FMAP_SIZE; i ++){
				Xil_Out32 ((u32) (XPAR_LENET5_AXI4_TOP_VITIS_0_BASEADDR + LENET_FMAP_ADDR), (u32) fmap_HW[i]);
				}

				XTime_GetTime(&tStart);
				Xil_Out32 ((u32) (XPAR_LENET5_AXI4_TOP_VITIS_0_BASEADDR + LENET_CE_ADDR), (u32) 1); // run

				while(1) {
					val = (int) Xil_In32 ((u32) (XPAR_LENET5_AXI4_TOP_VITIS_0_BASEADDR + CORE_DONE_ADDR));
          result_0_rtl1 = (int) Xil_In32 ((u32) (XPAR_LENET5_AXI4_TOP_VITIS_0_BASEADDR + RESULT_ADDR));
          printf("my result : %d\n", result_0_rtl1);
					if(val == 1)
          result_0_rtl2 = (int) Xil_In32 ((u32) (XPAR_LENET5_AXI4_TOP_VITIS_0_BASEADDR + RESULT_ADDR));
          printf("my result : %d\n", result_0_rtl2);
						break;
				}
				result_0_rtl0 = (int) Xil_In32 ((u32) (XPAR_LENET5_AXI4_TOP_VITIS_0_BASEADDR + RESULT_ADDR));
				Xil_Out32 ((u32) (XPAR_LENET5_AXI4_TOP_VITIS_0_BASEADDR + LENET_CE_ADDR), (u32) 0);
				XTime_GetTime(&tEnd);
				ref_v_run_cycle = 2*(tEnd - tStart);
				ref_v_run_time = 1.0 * (tEnd - tStart) / (COUNTS_PER_SECOND/1000000);
				printf("[RTL_V] Output took %llu clock cycles.\n", ref_v_run_cycle);
				printf("[RTL_V] Output took %.2f us.\n", ref_v_run_time);
				printf("[RTL_V] result : %d\n", result_0_rtl0);

				if(out_result != result_0_rtl0) {
					printf("[Mismatch] result_C : %d vs result_V : %d\n", out_inference_result, result_0_rtl0);
					print ("exit \r\n");
					//return 0;
          break;
				}
				printf("[Match] REF_C vs RTL_V \n");
				double perf_ratio = ref_c_run_cycle / ref_v_run_cycle;
				printf("[Match] RTL_V is  %.2f times faster than REF_C  \n", perf_ratio);
				printf("[Match] The difference between RTL_V and REF_C is %.2f us.  \n", ref_c_run_time - ref_v_run_time);
				break;
			case '2': // exit
				print ("exit \r\n");
				return 0;
		}
		print ("\r\n");
	}
    return 0;
}