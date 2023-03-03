#include <stdio.h>
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
  int result;
  
  FILE *fp_fmap;
  FILE *fp_weight1;
  FILE *fp_weight2;
  FILE *fp_weight2_ch1;
  FILE *fp_weight2_ch2;
  FILE *fp_weight2_ch3;
  FILE *fp_weight2_ch4;
  FILE *fp_weight_fc;
  FILE *fp_bias_fc;
  srand(time(NULL));
  signed int random;
  ////////////////////////////Generate random values////////////////////////////
  ////////////////////////////And save mem file////////////////////////////

  //////////////////////////////////////////fmap//////////////////////////////////////////
   /*fp_fmap = fopen("random_fmap.mem", "w");
	for (i = 0; i < ich1; i++) {
		for (m = 0; m < ichsize1; m++) {
			for (n = 0; n < ichsize1; n++) {
        random = rand()%255;
        fmap1[i][m][n] = random;
        if(n == ichsize1-1){
          if(fmap1[i][m][n]<16){
            fprintf(fp_fmap, "0%X",fmap1[i][m][n]);
          }
          else{
            fprintf(fp_fmap, "%X",fmap1[i][m][n]);
          }
        }
        else{
          if(fmap1[i][m][n]<16){
          fprintf(fp_fmap, "0%X ",fmap1[i][m][n]);
          }
        else{
          fprintf(fp_fmap, "%X ",fmap1[i][m][n]);
          }
        }
        
			}
      fprintf(fp_fmap, "\n");
		}
	}
  fclose(fp_fmap);
  //////////////////////////////////////////weight1 for conv1//////////////////////////////////////////
  fp_weight1 = fopen("random_weight1.mem", "w");
	for (i = 0; i < ich1; i++) {
		for (p = 0; p < och1; p++) {
			for (m = 0; m < ksize; m++) {
				for (n = 0; n < ksize; n++) {
          random = rand()%256 - 128;
          weight1[i][p][m][n] = random;
          if(random < 0){
            weight1_HW[i][p][m][n] = random + 256;
          }
          else{
            weight1_HW[i][p][m][n] = random;
          }
          if(n == ksize-1){
            if(weight1_HW[i][p][m][n]<16){
            fprintf(fp_weight1, "0%X", weight1_HW[i][p][m][n]);
            }
            else{
            fprintf(fp_weight1, "%X", weight1_HW[i][p][m][n]);
            }
          }
          else{
            if(weight1_HW[i][p][m][n]<16){
            fprintf(fp_weight1, "0%X ", weight1_HW[i][p][m][n]);
            }
            else{
            fprintf(fp_weight1, "%X ", weight1_HW[i][p][m][n]);
            }
          }
				}
        fprintf(fp_weight1, "\n");
			}
		}
	}
  fclose(fp_weight1);*/
  
  //////////////////////////////////////////weight2 for conv2//////////////////////////////////////////
  /*fp_weight2 = fopen("random_weight2.mem", "w");
	for (i = 0; i < ich2; i++) {
		for (p = 0; p < och2; p++) {
			for (m = 0; m < ksize; m++) {
				for (n = 0; n < ksize; n++) {
          random = rand()%256 - 128;
          weight2[i][p][m][n] = random;
          if(random < 0){
            weight2_HW[i][p][m][n] = random + 256;
          }
          else{
            weight2_HW[i][p][m][n] = random;
          }
          if(n == ksize-1){
            if(weight2_HW[i][p][m][n]<16){
            fprintf(fp_weight1, "0%X", weight2_HW[i][p][m][n]);
            }
            else{
            fprintf(fp_weight1, "%X", weight2_HW[i][p][m][n]);
            }
          }
          else{
            if(weight2_HW[i][p][m][n]<16){
            fprintf(fp_weight1, "0%X ", weight2_HW[i][p][m][n]);
            }
            else{
            fprintf(fp_weight1, "%X ", weight2_HW[i][p][m][n]);
            }
          }
				}
        fprintf(fp_weight2, "\n");
			}
		}
	}
  fclose(fp_weight2);

  fp_weight2_ch1 = fopen("random_weight2_ch1.mem", "w");
  fp_weight2_ch2 = fopen("random_weight2_ch2.mem", "w");
  fp_weight2_ch3 = fopen("random_weight2_ch3.mem", "w");
  fp_weight2_ch4 = fopen("random_weight2_ch4.mem", "w");
  for (i = 0; i < ich2; i++) {
    for (p = 0; p < och2; p++) {
			for (m = 0; m < ksize; m++) {
				for (n = 0; n < ksize; n++) {
          if(i == 0){
            if(weight2_HW[i][p][m][n]<16){
              if(n == ksize-1){
                fprintf(fp_weight2_ch1, "0%X", weight2_HW[i][p][m][n]);
                fprintf(fp_weight2_ch1, "\n");
              }
              else{
                fprintf(fp_weight2_ch1, "0%X ", weight2_HW[i][p][m][n]);
              }
            }
            else{
              if(n == ksize-1){
                fprintf(fp_weight2_ch1, "%X", weight2_HW[i][p][m][n]);
                fprintf(fp_weight2_ch1, "\n");
              }
              else{
                fprintf(fp_weight2_ch1, "%X ", weight2_HW[i][p][m][n]);
              }
            }
          }
          else if(i == 1){
            if(weight2_HW[i][p][m][n]<16){
              if(n == ksize-1){
                fprintf(fp_weight2_ch2, "0%X", weight2_HW[i][p][m][n]);
                fprintf(fp_weight2_ch2, "\n");
              }
              else{
                fprintf(fp_weight2_ch2, "0%X ", weight2_HW[i][p][m][n]);
              }
            }
            else{
              if(n == ksize-1){
                fprintf(fp_weight2_ch2, "%X", weight2_HW[i][p][m][n]);
                fprintf(fp_weight2_ch2, "\n");
              }
              else{
                fprintf(fp_weight2_ch2, "%X ", weight2_HW[i][p][m][n]);
              }
            }
          }
          else if(i == 2){
            if(weight2_HW[i][p][m][n]<16){
              if(n == ksize-1){
                fprintf(fp_weight2_ch3, "0%X", weight2_HW[i][p][m][n]);
                fprintf(fp_weight2_ch3, "\n");
              }
              else{
                fprintf(fp_weight2_ch3, "0%X ", weight2_HW[i][p][m][n]);
              }
            }
            else{
              if(n == ksize-1){
                fprintf(fp_weight2_ch3, "%X", weight2_HW[i][p][m][n]);
                fprintf(fp_weight2_ch3, "\n");
              }
              else{
                fprintf(fp_weight2_ch3, "%X ", weight2_HW[i][p][m][n]);
              }
            }
          }
          else if(i == 3){
            if(weight2_HW[i][p][m][n]<16){
              if(n == ksize-1){
                fprintf(fp_weight2_ch4, "0%X", weight2_HW[i][p][m][n]);
                fprintf(fp_weight2_ch4, "\n");
              }
              else{
                fprintf(fp_weight2_ch4, "0%X ", weight2_HW[i][p][m][n]);
              }
            }
            else{
              if(n == ksize-1){
                fprintf(fp_weight2_ch4, "%X", weight2_HW[i][p][m][n]);
                fprintf(fp_weight2_ch4, "\n");
              }
              else{
                fprintf(fp_weight2_ch4, "%X ", weight2_HW[i][p][m][n]);
              }
            }
          }
        }
      }
    }
  }
  fclose(fp_weight2_ch1);
  fclose(fp_weight2_ch2);
  fclose(fp_weight2_ch3);
  fclose(fp_weight2_ch4);
*/
  /*fp_weight_fc = fopen("random_weight_fc.mem", "w");
	for (i = 0; i < och3; i++) {
		for (p = 0; p < ich3; p++) {
      random = rand()%256 - 128;
      weight_fc[i][p] = random;
      if(random < 0){
        weight_fc_HW[i][p] = random + 256;
      }
      else{
        weight_fc_HW[i][p] = random;
      }
      if(p == ich3-1){
        if(weight_fc_HW[i][p]<16){
        fprintf(fp_weight_fc, "0%X", weight_fc_HW[i][p]);
        }
        else{
        fprintf(fp_weight_fc, "%X", weight_fc_HW[i][p]);
        }
      }
      else{
        if(weight_fc_HW[i][p]<16){
        fprintf(fp_weight_fc, "0%X ", weight_fc_HW[i][p]);
        }
        else{
        fprintf(fp_weight_fc, "%X ", weight_fc_HW[i][p]);
        }
      }
		}
    fprintf(fp_weight_fc, "\n");
	}
  fclose(fp_weight_fc);

  fp_bias_fc = fopen("random_bias_fc.mem", "w");
	for (i = 0; i < och3; i++) {
    random = rand()%32768 - 16384; //15bit -16384~16383
    random = random*2; //16bit -32768~32765
    bias_fc[i] = random;
    if(random < 0){
      bias_fc_HW[i] = random + 65536;
    }
    else{
      bias_fc_HW[i] = random;
    }
      if(bias_fc_HW[i]<16){
      fprintf(fp_bias_fc, "000%X", bias_fc_HW[i]);
      fprintf(fp_bias_fc, "\n");
      }
      else if((bias_fc_HW[i]>=16)&&(bias_fc_HW[i]<16*16)){
      fprintf(fp_bias_fc, "00%X", bias_fc_HW[i]);
      fprintf(fp_bias_fc, "\n");
      }
    
      else if((bias_fc_HW[i]>=16*16)&&(bias_fc_HW[i]<16*16*16)){
      fprintf(fp_bias_fc, "0%X", bias_fc_HW[i]);
      fprintf(fp_bias_fc, "\n");
      }
      else if((bias_fc_HW[i]>=16*16*16)&&(bias_fc_HW[i]<16*16*16*16)){
      fprintf(fp_bias_fc, "%X", bias_fc_HW[i]);
      fprintf(fp_bias_fc, "\n");
    }
	}
  fclose(fp_bias_fc);
*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////Real values////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
fp_fmap = fopen("SW_test_num9_1.txt", "r");
	for (i = 0; i < ich1; i++) {
		for (m = 0; m < ichsize1; m++) {
			for (n = 0; n < ichsize1; n++) {
        fscanf(fp_fmap,"%d",&fmap1[i][m][n]);
			}
		}
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
  printf("\n[Final result = %d]\n",result);
	return 0;
}