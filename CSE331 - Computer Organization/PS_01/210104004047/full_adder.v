module full_adder (
    input a,
    input b,
    input cin,
    output sum,
    output cout
);
    wire xor1_out, and1_out, and2_out;

    // Sum calculation
    xor (xor1_out, a, b);
    xor (sum, xor1_out, cin);

    // Carry-out calculation
    and (and1_out, a, b);
    and (and2_out, xor1_out, cin); // This line is changed
    or (cout, and1_out, and2_out);
endmodule