module mux_2to1_5bit(input [4:0] a, b, input sel, output wire [4:0] y);
	
	assign y = sel ? b : a;

endmodule