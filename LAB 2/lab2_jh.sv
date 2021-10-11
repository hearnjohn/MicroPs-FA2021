module lab2_jh(input clk,
					input s1[3:0],
					input s2[3:0],
					output anode1,
					output anode2,
					output led[4:0],
					output [6:0] seg);

	logic powered;
	// Compute LED logic
	assign led[0] = s1[0] ^ s2[0];
	assign led[1] = (s1[1] ^ s2[1]) ^ (s1[0] & s2[0]);
	assign led[2] = (s1[2] ^ s2[2]) ^ (s1[1] & s2[1]);
	assign led[3] = (s1[3] ^ s2[3]) ^ (s1[2] & s2[2]);
	assign led[4] = s1[3] & s2[3];
	
	// if powered -> turn on display 1, compute the proper digit to display
	// else turn on display 2, compute the proper digit to display
	poweredSwitch(clk, powered);
	logic num[3:0];
	
	assign num = powered ? s2 : s1;
	assignSegments(num, seg);
	
	assign anode1 = powered;
	assign anode2 = ~powered;
	
endmodule


// Using clock input determine which display should be powered
module poweredSwitch(input logic clk,
							output logic powered);
	logic [29:0] q;
	always_ff @(posedge clk)
		q <= q + 89485;
		assign powered = q[29];
	
endmodule


// Compute using switch inputs which segments turn on with the display
module assignSegments(input logic s[3:0],
					  output logic [6:0] seg);
	// Number segment display logic
	// bits go in order  gfedcba
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