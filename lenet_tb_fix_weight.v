`timescale 1ns / 1ps
module lenet_tb_fix_weight;
`include "param_clog2.vh"
localparam cnt_feature = clog2(I_SIZE1*I_SIZE1);
	// Inputs
reg clk;
reg ce;
reg global_rst_n;
reg [I_BW1-1:0] r_i_fmap;

wire [3:0] w_o_classification_result;
wire w_o_classification_en;
wire w_o_classification_end;
	////////////////////////////////////////
  //////////instantiation lenet5 module//////////
	////////////////////////////////////////
  lenet5_fix_weight u_lenet5_fix_weight(
    .clk(clk), .ce(ce), .global_rst_n(global_rst_n), .i_rst_processEnd(w_o_classification_end),
    .i_fmap(r_i_fmap),
    .o_classification_result(w_o_classification_result), .o_classification_en(w_o_classification_en), .o_classification_end(w_o_classification_end)
  );

always@(posedge clk) begin
	if(w_o_classification_end == 1'b1) begin
  $stop;
    end
  end
reg [cnt_feature:0] in_fmap_count;
reg [I_BW1-1:0] in_fmap [0:(I_SIZE1*I_SIZE1)-1];

always @(posedge clk) begin
  if(ce)begin
	if(in_fmap_count!=I_SIZE1*I_SIZE1) begin
	    in_fmap_count <= in_fmap_count+1;
		r_i_fmap <= in_fmap[in_fmap_count];
	end
	else begin
		in_fmap_count <= in_fmap_count;
	end
  end
end
initial begin
	$readmemh("HW_test_num3_1.mem", in_fmap);
end
initial begin
in_fmap_count <= 0;
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