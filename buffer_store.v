`timescale 1ns / 1ps
module buffer_store #(parameter BW = 8, SIZE = 5, CO = 4)
(
  clk, ce, global_rst_n, rst_processEnd,
  i_data,
  o_data, o_empty, o_full
);
`include "clog2_function.vh"
localparam cnt_size = clog2(CO*SIZE*SIZE);
localparam i_size = CO*SIZE*SIZE;

input signed [BW-1:0] i_data;
input clk, ce, global_rst_n, rst_processEnd;
output signed [(i_size*BW)-1:0] o_data;
output o_empty, o_full;

reg signed [BW-1:0]       r_buffer [0:(i_size)-1];
reg [cnt_size-1:0] r_cnt;
reg r_empty;
reg r_full;
integer i;

always @(posedge clk or negedge global_rst_n) begin
  if(!global_rst_n) begin
    r_cnt <= {(cnt_size){1'b0}};
    r_empty <= 1'b0;
    r_full <= 1'b0;
    for(i=0;i<i_size;i=i+1) begin
      r_buffer[i] <= {(BW){1'b0}};
    end
  end
  else if(rst_processEnd) begin
    r_cnt <= {(cnt_size){1'b0}};
    r_empty <= 1'b0;
    r_full <= 1'b0;
    for(i=0;i<i_size;i=i+1) begin
      r_buffer[i] <= {(BW){1'b0}};
    end
  end
  
  else if(ce) begin
    if(r_cnt != i_size) begin
      r_buffer[r_cnt] <= i_data;
      r_cnt <= r_cnt + 1;
      r_full <= 1'b0;
      r_empty <= 1'b1;
    end
    else if(r_cnt == i_size) begin
      r_cnt <= r_cnt;
      r_full <= 1'b1;
      r_empty <= 1'b0;
    end
  end
end

generate
  genvar k;
  for(k=0;k<i_size;k=k+1) begin
    assign o_data[k*BW +: BW] = r_buffer[k][BW-1:0];
  end
endgenerate
assign o_empty = r_empty;
assign o_full  = r_full;

endmodule