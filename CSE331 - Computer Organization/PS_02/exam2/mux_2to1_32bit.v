module mux_2to1_32bit(input [31:0] a, b, input sel, output wire [31:0] y);
	
	assign y = sel ? b : a;

endmodule