module lab1_jh(input clk,
					input s[3:0],
					output led[7:0],
					output [6:0] seg);
	
	// Compute LED logic
	assign led[0] = s[0];
	assign led[1] = ~s[0];
	assign led[2] = s[1];
	assign led[3] = ~s[1];
	assign led[4] = s[2];
	assign led[5] = ~s[2];
	and g5(led[6], s[2], s[3]);
	
	counter(clk, led[7]);
	
	// Number segment display logic
	// bits of seg[6:0] go in order of gfedcba, which correspond to a segment
	always_comb
		case(s[3:0])
		4'b0000: seg = 7'b1000000;
		4'b0001: seg = 7'b1111001;
		4'b0010: seg = 7'b0100100;
		4'b0011: seg = 7'b0110000;
		4'b0100: seg = 7'b0011001;
		4'b0101: seg = 7'b0010010;
		4'b0110: seg = 7'b0000010;
		4'b0111: seg = 7'b1111000;
		4'b1000: seg = 7'b0000000;
		4'b1001: seg = 7'b0011000;
		4'b1010: seg = 7'b0001000;
		4'b1011: seg = 7'b0000011;
		4'b1100: seg = 7'b1000110;
		4'b1101: seg = 7'b0100001;
		4'b1110: seg = 7'b0000110;
		4'b1111: seg = 7'b0001110;
		default: seg = 7'b1111111;
		endcase
	
endmodule

// Get clock input and create a divide-by-2^N counter
// Was found that N = 30 and p = 214 is a precise combination for a 2.4Hz output
module counter (input logic clk,
					 output logic high);
	logic [29:0] q;
	always_ff @(posedge clk)
		q <= q + 214;
		assign high = q[29];

endmodule