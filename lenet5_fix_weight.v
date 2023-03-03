`timescale 1ns / 1ps
module lenet5_fix_weight
(
  clk, ce, global_rst_n, i_rst_processEnd, i_fmap,
  o_classification_result, o_classification_en, o_classification_end
);
`include "param_clog2.vh"
localparam cnt_weight1 = clog2(CO1*K_SIZE*K_SIZE);
localparam cnt_weight2 = clog2(CO2*K_SIZE*K_SIZE);
localparam cnt_weight_fc = clog2(CI3*CO3*I_SIZE3*I_SIZE3);
localparam cnt_bias_fc = clog2(CO3);

  input clk, ce, global_rst_n, i_rst_processEnd;
  input signed [I_BW1-1:0] i_fmap;
  output signed   [3:0] o_classification_result;
  output                o_classification_en, o_classification_end;
  reg [W_BW-1:0]  r_i_weight1;
  reg [W_BW-1:0]  r_i_weight2_ch1;
  reg [W_BW-1:0]  r_i_weight2_ch2;
  reg [W_BW-1:0]  r_i_weight2_ch3;
  reg [W_BW-1:0]  r_i_weight2_ch4;
  reg [W_BW-1:0]  r_i_weight_fc;
  reg [B_BW-1:0]  r_i_bias_fc;
  reg r_ce;
  always @(posedge clk or negedge global_rst_n) begin
    if(!global_rst_n) begin
      r_ce <= 1'b0;
    end
    else begin
      r_ce <= ce;
    end
  end
  wire [CO1*K_SIZE*K_SIZE*W_BW-1:0] w_weight1;
  wire [CI2*CO2*K_SIZE*K_SIZE*W_BW-1:0] w_weight2;
  wire [CO2*K_SIZE*K_SIZE*W_BW-1:0] w_weight2_ch1;
  wire [CO2*K_SIZE*K_SIZE*W_BW-1:0] w_weight2_ch2;
  wire [CO2*K_SIZE*K_SIZE*W_BW-1:0] w_weight2_ch3;
  wire [CO2*K_SIZE*K_SIZE*W_BW-1:0] w_weight2_ch4;
  wire [CI3*CO3*I_SIZE3*I_SIZE3*W_BW-1:0] w_weight_fc;
  wire [CO3*B_BW-1:0] w_bias_fc;

  wire rst_processEnd;
  wire w_empty1;
  wire w_full1;
  wire w_empty2_ch1, w_empty2_ch2, w_empty2_ch3, w_empty2_ch4;
  wire w_full2_ch1, w_full2_ch2, w_full2_ch3, w_full2_ch4;
  wire w_empty_fc;
  wire w_full_fc;
  wire w_empty_fc_bias;
  wire w_full_fc_bias;

  wire [3:0] w_o_fc_data;
  wire w_fc_end;
  wire w_fc_en;

  wire [O_BW1-1:0] w_conv1_result;
  wire w_conv1_en;
  wire w_convlayer1_ch_end;
  wire w_convlayer1_allch_end;

  wire [O_BW2-1:0] w_conv2_result;
  wire w_conv2_en;
  wire w_convlayer2_ch_end;
  wire w_convlayer2_allch_end;

  reg [cnt_weight1:0] in_weight1_count;
  reg [cnt_weight2:0] in_weight2_ch1_count, in_weight2_ch2_count, in_weight2_ch3_count, in_weight2_ch4_count;
  reg [cnt_weight_fc:0] in_weight_fc_count;
  reg [cnt_bias_fc:0]   in_bias_fc_count;

  reg [W_BW-1:0] in_weight1 [0:(CO1*K_SIZE*K_SIZE)-1];
  reg [W_BW-1:0] in_weight2_ch1 [0:(CO2*K_SIZE*K_SIZE)-1];
  reg [W_BW-1:0] in_weight2_ch2 [0:(CO2*K_SIZE*K_SIZE)-1];
  reg [W_BW-1:0] in_weight2_ch3 [0:(CO2*K_SIZE*K_SIZE)-1];
  reg [W_BW-1:0] in_weight2_ch4 [0:(CO2*K_SIZE*K_SIZE)-1];
  reg [W_BW-1:0] in_weight_fc [0:(CI3*CO3*I_SIZE3*I_SIZE3)-1];
  reg [B_BW-1:0] in_bias_fc [0:CO3-1];

  always @(posedge clk or negedge global_rst_n) begin
		if(ce)begin
			if(in_weight1_count!=CI1*CO1*K_SIZE*K_SIZE) begin
		  in_weight1_count <= in_weight1_count+1;	
		  r_i_weight1 <= in_weight1[in_weight1_count];
			end
			else begin
			in_weight1_count <= in_weight1_count;
			end
		end
    else if(!global_rst_n) begin
      in_weight1_count <= 0;
    end
	end

  always @(posedge clk or negedge global_rst_n) begin
		if(ce)begin
			if(in_weight2_ch1_count!=CO2*K_SIZE*K_SIZE) begin
		  in_weight2_ch1_count <= in_weight2_ch1_count+1;	
		  r_i_weight2_ch1 <= in_weight2_ch1[in_weight2_ch1_count];
			end
			else begin
			in_weight2_ch1_count <= in_weight2_ch1_count;
			end
		end
    else if(!global_rst_n) begin
      in_weight2_ch1_count <= 0;
    end
	end
  always @(posedge clk or negedge global_rst_n) begin
		if(ce)begin
			if(in_weight2_ch2_count!=CO2*K_SIZE*K_SIZE) begin
		  in_weight2_ch2_count <= in_weight2_ch2_count+1;	
		  r_i_weight2_ch2 <= in_weight2_ch2[in_weight2_ch2_count];
			end
			else begin
			in_weight2_ch2_count <= in_weight2_ch2_count;
			end
		end
    else if(!global_rst_n) begin
      in_weight2_ch2_count <= 0;
    end
	end
  always @(posedge clk or negedge global_rst_n) begin
		if(ce)begin
			if(in_weight2_ch3_count!=CO2*K_SIZE*K_SIZE) begin
		  in_weight2_ch3_count <= in_weight2_ch3_count+1;	
		  r_i_weight2_ch3 <= in_weight2_ch3[in_weight2_ch3_count];
			end
			else begin
			in_weight2_ch3_count <= in_weight2_ch3_count;
			end
		end
    else if(!global_rst_n) begin
      in_weight2_ch3_count <= 0;
    end
	end
  always @(posedge clk or negedge global_rst_n) begin
		if(ce)begin
			if(in_weight2_ch4_count!=CO2*K_SIZE*K_SIZE) begin
		  in_weight2_ch4_count <= in_weight2_ch4_count+1;	
		  r_i_weight2_ch4 <= in_weight2_ch4[in_weight2_ch4_count];
			end
			else begin
			in_weight2_ch4_count <= in_weight2_ch4_count;
			end
		end
    else if(!global_rst_n) begin
      in_weight2_ch4_count <= 0;
    end
	end
  always @(posedge clk or negedge global_rst_n) begin
		if(ce)begin
			if(in_weight_fc_count!=CI3*CO3*I_SIZE3*I_SIZE3) begin
		  in_weight_fc_count <= in_weight_fc_count+1;	
		  r_i_weight_fc <= in_weight_fc[in_weight_fc_count];
			end
			else begin
			in_weight_fc_count <= in_weight_fc_count;
			end
		end
    else if(!global_rst_n) begin
      in_weight_fc_count <= 0;
    end
	end
  always @(posedge clk or negedge global_rst_n) begin
		if(ce)begin
			if(in_bias_fc_count!=CO3) begin
		  in_bias_fc_count <= in_bias_fc_count+1;	
		  r_i_bias_fc <= in_bias_fc[in_bias_fc_count];
			end
			else begin
			in_bias_fc_count <= in_bias_fc_count;
			end
		end
    else if(!global_rst_n) begin
      in_bias_fc_count <= 0;
    end
	end
  initial begin
    $readmemh("HW_conv1_weight.mem", in_weight1);
    $readmemh("HW_conv2_weight_ch1.mem", in_weight2_ch1);
    $readmemh("HW_conv2_weight_ch2.mem", in_weight2_ch2);
    $readmemh("HW_conv2_weight_ch3.mem", in_weight2_ch3);
    $readmemh("HW_conv2_weight_ch4.mem", in_weight2_ch4);
    $readmemh("HW_fc_weight.mem", in_weight_fc);
    $readmemh("HW_fc_bias.mem", in_bias_fc);
	end
  //////////instantiation buffer to store weights of convolution layer 1//////////
  buffer_store #(.BW(W_BW),.SIZE(K_SIZE),.CO(CO1)) u_weight_buffer_store1
  (
    .clk(clk),.ce(r_ce),.global_rst_n(global_rst_n),.rst_processEnd(i_rst_processEnd),.i_data(r_i_weight1),.o_data(w_weight1),.o_empty(w_empty1),.o_full(w_full1)
  );
  //////////instantiation buffer to store weights of convolution layer 2//////////
  //////////////////////////////Ch1//////////////////////////////
  buffer_store #(.BW(W_BW),.SIZE(K_SIZE),.CO(CO2)) u_weight_buffer_store2_ch1
  (
    .clk(clk),.ce(r_ce),.global_rst_n(global_rst_n),.rst_processEnd(i_rst_processEnd),.i_data(r_i_weight2_ch1),.o_data(w_weight2_ch1),.o_empty(w_empty2_ch1),.o_full(w_full2_ch1)
  );
  //////////////////////////////Ch2//////////////////////////////
  buffer_store #(.BW(W_BW),.SIZE(K_SIZE),.CO(CO2)) u_weight_buffer_store2_ch2
  (
    .clk(clk),.ce(r_ce),.global_rst_n(global_rst_n),.rst_processEnd(i_rst_processEnd),.i_data(r_i_weight2_ch2),.o_data(w_weight2_ch2),.o_empty(w_empty2_ch2),.o_full(w_full2_ch2)
  );
  //////////////////////////////Ch3//////////////////////////////
  buffer_store #(.BW(W_BW),.SIZE(K_SIZE),.CO(CO2)) u_weight_buffer_store2_ch3
  (
    .clk(clk),.ce(r_ce),.global_rst_n(global_rst_n),.rst_processEnd(i_rst_processEnd),.i_data(r_i_weight2_ch3),.o_data(w_weight2_ch3),.o_empty(w_empty2_ch3),.o_full(w_full2_ch3)
  );
  //////////////////////////////Ch4//////////////////////////////
  buffer_store #(.BW(W_BW),.SIZE(K_SIZE),.CO(CO2)) u_weight_buffer_store2_ch4
  (
    .clk(clk),.ce(r_ce),.global_rst_n(global_rst_n),.rst_processEnd(i_rst_processEnd),.i_data(r_i_weight2_ch4),.o_data(w_weight2_ch4),.o_empty(w_empty2_ch4),.o_full(w_full2_ch4)
  );
  //////////instantiation buffer to store weights of fully connected layer //////////
  buffer_store_fcweight #(.BW(W_BW),.SIZE(I_SIZE3),.CI(CI3),.CO(CO3)) u_weight_buffer_store_fc
  (
    .clk(clk),.ce(r_ce),.global_rst_n(global_rst_n),.rst_processEnd(i_rst_processEnd),.i_data(r_i_weight_fc),.o_data(w_weight_fc),.o_empty(w_empty_fc),.o_full(w_full_fc)
  );
  //////////instantiation buffer to store biases of fully connected layer //////////
  buffer_store #(.BW(B_BW),.SIZE(1),.CO(CO3)) u_bias_buffer_store_fc
  (
    .clk(clk),.ce(r_ce),.global_rst_n(global_rst_n),.rst_processEnd(i_rst_processEnd),.i_data(r_i_bias_fc),.o_data(w_bias_fc),.o_empty(w_empty_fc_bias),.o_full(w_full_fc_bias)
  );

  //////////instantiation Convolution layer 1//////////
  Conv_layer1 #(.mem_ifmap_addr_width(mem_ifmap1_addr_width),.mem_ifmap_bit_width(mem_ifmap1_bit_width),.mem_ifmap_depth(mem_ifmap1_depth),
  .I_SIZE(I_SIZE1),.O_SIZE(O_SIZE1),.I_BW(I_BW1),.W_BW(W_BW),.O_BW(O_BW1),
  .O_CONV_BW(O_CONV_BW1),.CI(CI1),.CO(CO1),.K_SIZE(K_SIZE),.P_SIZE(P_SIZE))
  u_Conv_layer1
  (
    .clk(clk),.ce(ce),.global_rst_n(global_rst_n),.rst_processEnd(i_rst_processEnd),.i_fmap(i_fmap),.i_weight(w_weight1),
    .o_conv1_result(w_conv1_result),.o_convlayer1_en(w_conv1_en),
    .o_convlayer1_ch_end(w_convlayer1_ch_end),.o_convlayer1_allch_end(w_convlayer1_allch_end)
  );
  assign w_weight2[1*CO2*K_SIZE*K_SIZE*W_BW-1:0*CO2*K_SIZE*K_SIZE*W_BW] = w_weight2_ch1;
  assign w_weight2[2*CO2*K_SIZE*K_SIZE*W_BW-1:1*CO2*K_SIZE*K_SIZE*W_BW] = w_weight2_ch2;
  assign w_weight2[3*CO2*K_SIZE*K_SIZE*W_BW-1:2*CO2*K_SIZE*K_SIZE*W_BW] = w_weight2_ch3;
  assign w_weight2[4*CO2*K_SIZE*K_SIZE*W_BW-1:3*CO2*K_SIZE*K_SIZE*W_BW] = w_weight2_ch4;

  //////////instantiation Convolution layer2//////////
  Conv_layer2 #(.mem_ifmap_addr_width(mem_ifmap2_addr_width),.mem_ifmap_bit_width(mem_ifmap2_bit_width),.mem_ifmap_depth(mem_ifmap2_depth),
  .I_SIZE(I_SIZE2),.O_SIZE(O_SIZE2),.I_BW(I_BW2),.W_BW(W_BW),.O_BW(O_BW2),
  .O_CONV_BW(O_CONV_BW2),.O_CONVSUM_BW(O_CONVSUM_BW2),.CI(CI2),.CO(CO2),.K_SIZE(K_SIZE),.P_SIZE(P_SIZE))
  u_Conv_layer2
  (
    .clk(clk),.ce(w_conv1_en),.global_rst_n(global_rst_n),.rst_processEnd(i_rst_processEnd),
    .i_fmap(w_conv1_result),.i_weight(w_weight2),.i_convlayer1_ch_end(w_convlayer1_ch_end),
    .o_conv2_result(w_conv2_result),.o_convlayer2_en(w_conv2_en),
    .o_convlayer2_ch_end(w_convlayer2_ch_end),.o_convlayer2_allch_end(w_convlayer2_allch_end)
  );

  //////////instantiation FC layer//////////
  fc_layer #(.I_BW(I_BW3),.W_BW(W_BW),.B_BW(B_BW),.O_BW(O_BW3),
  .O_FCSUM_BW(O_FCSUM_BW3),.I_SIZE(I_SIZE3),.CI(CI3),.CO(CO3)) u_fc_layer
  (
    .clk(clk), .ce(w_conv2_en), .global_rst_n(global_rst_n), .rst_processEnd(i_rst_processEnd),
    .i_data(w_conv2_result), .i_weight(w_weight_fc), .i_bias(w_bias_fc), .o_data(w_o_fc_data), .o_en(w_fc_en), .o_end(w_fc_end)
  );
  
  assign o_classification_result = w_o_fc_data;
  assign o_classification_en = w_fc_en;
  assign o_classification_end = w_fc_end;  
endmodule