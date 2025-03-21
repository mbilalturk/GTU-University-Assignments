
// Top-Level Single Cycle MIPS Processor
module SingleCycleMIPS(
    input clk,
    input rst
);
    wire [31:0] pc, next_pc, alu_src_mux_out, instruction, write_data, read_data1, read_data2, alu_result, read_data_mem, sign_ext_imm;
    wire [4:0] write_reg;
    wire [2:0] alu_control;
    wire reg_dst, alu_src, mem_to_reg, reg_write, mem_read, mem_write, branch, zero;
	 
	 
    // Modules
    PcModule pc_module(.clk(clk), .rst(rst), .next_pc(next_pc), .pc(pc));
    InstructionFetch if_module(.pc(pc), .instruction(instruction));
    RegisterFile rf_module(.clk(clk), .we(reg_write), .rs(instruction[25:21]), .rt(instruction[20:16]), .rd(write_reg), .write_data(write_data), .read_data1(read_data1), .read_data2(read_data2));
    AluModule alu_module(.src1(read_data1), .src2(alu_src_mux_out), .alu_control(alu_control), .result(alu_result), .zero(zero));
    DataMemory dm_module(.clk(clk), .we(mem_write), .address(alu_result), .write_data(read_data2), .read_data(read_data_mem));
    ControlUnit cu_module(.opcode(instruction[31:26]), .funct(instruction[5:0]), .reg_dst(reg_dst), .alu_src(alu_src), .mem_to_reg(mem_to_reg), .reg_write(reg_write), .mem_read(mem_read), .mem_write(mem_write), .branch(branch), .alu_control(alu_control));
	 
	 assign sign_ext_imm			= {(instruction[15] ? 16'hFFFF : 16'h0000), instruction[15:0]};
	 
	
		// wire [31:0] res;
		// wire zero2;
		// AluModule alu_module2(.src1(pc + 32'b0100), .src2(sign_ext_imm << 2), .alu_control(alu_control), .result(res), .zero(zero2));
		// mux_2to1_32bit mux(.a(res), .b(pc + 32'b0100), .sel(zero & branch));
	
	 
	 //Additional logic here (e.g., branch calculations, muxes, etc.)
	 //You can use ternary operator as a MUX: A ? B : C, which means if A is true do B else do C
	 // assign alu_src_mux_out  		= 
	 //assign write_data 			= 
	 assign next_pc					=  pc + 4;
	 //assign write_reg 				= 
	 
	 
	 
endmodule
