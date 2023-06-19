/*******************************************************************************
#Author: Seungmin.Jeong(Graduated from Kwangwoon University, Seoul, Korea 2023.02)
#Purpose: verilog code / lenet testbench
#Revision History: 2023.03.03
*******************************************************************************/
`timescale 1ns / 1ps
module lenet5_tb;
`include "param_clog2.vh"
localparam SIZE1 = K_SIZE*K_SIZE*CI1*CO1;
localparam SIZE2 = K_SIZE*K_SIZE*CI2*CO2;
localparam SIZE3 = I_SIZE3*I_SIZE3*CI3*CO3;
localparam cnt_feature = clog2(I_SIZE1*I_SIZE1);
localparam cnt_weight = clog2(SIZE1+SIZE2+SIZE3);
localparam cnt_bias = clog2(CO3);
	// Inputs
reg clk;
reg ce;
reg global_rst_n;
reg [I_BW1-1:0] r_i_fmap;
reg [W_BW-1:0]  r_i_weight;
reg [B_BW-1:0]  r_i_bias_fc;

wire [3:0] w_o_classification_result;
wire w_o_classification_en;
wire w_o_classification_end;
	////////////////////////////////////////
  //////////instantiation lenet5 module//////////
	////////////////////////////////////////
  lenet5 u_lenet5(
    .clk(clk), .ce(ce), .global_rst_n(global_rst_n), .i_rst_processEnd(w_o_classification_end),
    .i_fmap(r_i_fmap),.i_weight(r_i_weight),.i_bias_fc(r_i_bias_fc),
    .o_classification_result(w_o_classification_result), .o_classification_en(w_o_classification_en), .o_classification_end(w_o_classification_end)
  );

initial begin
	$readmemh("HW_Weight.mem", in_weight);
	$readmemh("HW_Bias.mem", in_bias);
	$readmemh("HW_test_num3_1.mem", in_fmap);
end
always@(posedge clk) begin
	if(w_o_classification_en == 1'b1) begin
  $display("The real number = 3, The inference result = %d",w_o_classification_result);
  $stop;
    end
  end
reg [cnt_feature:0] in_fmap_count;
reg [I_BW1-1:0] in_fmap [0:(I_SIZE1*I_SIZE1)-1];
reg [cnt_weight:0] in_weight_count;
reg [W_BW-1:0] in_weight [0:(SIZE1+SIZE2+SIZE3)-1];
reg [cnt_bias:0] in_bias_count;
reg [B_BW-1:0] in_bias [0:(CO3)-1];

reg DONE1;
reg DONE2;
reg DONE3;
always @(posedge clk) begin
  if(ce)begin
	if(in_weight_count!=SIZE1+SIZE2+SIZE3) begin
	    in_weight_count <= in_weight_count+1;
		r_i_weight <= in_weight[in_weight_count];
	end
	else begin
		in_weight_count <= in_weight_count;
		DONE1 <= 1'b1;
	end
  end
end
always @(posedge clk) begin
  if(ce&&DONE1)begin
	if(in_bias_count!=CO3) begin
	    in_bias_count <= in_bias_count+1;
		r_i_bias_fc <= in_bias[in_bias_count];
	end
	else begin
		in_bias_count <= in_bias_count;
		DONE2 <= 1'b1;
	end
  end
end
always @(posedge clk) begin
  if(ce&&DONE2)begin
	if(in_fmap_count!=I_SIZE1*I_SIZE1) begin
	    in_fmap_count <= in_fmap_count+1;
		r_i_fmap <= in_fmap[in_fmap_count];
	end
	else begin
		in_fmap_count <= in_fmap_count;
		DONE3 <= 1'b1;
	end
  end
end

initial begin
in_fmap_count <= 0;
in_weight_count <= 0;
in_bias_count <= 0;
DONE1 <= 0;
DONE2 <= 0;
DONE3 <= 0;
clk = 0;
ce = 0;
global_rst_n = 0;
#2
global_rst_n = 1;
#2
global_rst_n = 0;
#2
global_rst_n = 1;  
#2;
clk = 0;
ce = 0;
#4;	
ce=1;
end
always #(clkp/2) clk=~clk;      
endmodule