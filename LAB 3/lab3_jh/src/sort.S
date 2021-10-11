// sort.S
// Main sort function 
// jmhearn@hmc.edu
// 9/21/21

// Directives 
.syntax unified // Specify the syntax for the file
.cpu cortex-m4  // Target CPU is Cortex-M4
.fpu softvfp    // Use software libraries for floating-point operations
.thumb          // Instructions should be encoded as Thumb instructions

// Define main globally for other files to call
.global main

// Create test array of bytes. Change this for different test cases.
// This will get loaded to the RAM by the startup code (address 0x20000000)
.data
arr:
    .byte 12, 11, 10, 6, 5, 4, 3, 2, 1, 15, 14, 13
.size arr, .-arr

.text
// The main function

.type main, %function
main:
  ldr r3, =arr // Load the base address of RAM where the array is stored
  // YOUR CODE HERE
  mov r0, #0  // i = 0

loop_i:
  cmp r0, #11  // i == 11?
  bge done  // if i == 11 we're done
  mov r1, #0  // j = 0

loop_j:
  cmp r1, #11  // j < 11?
  bge done_j  // if j > 11 - 1 the inner loop is done

  // compare arr[j] with arr[j+1]

  add r5, r1, #1  // r5 = j + 1;
  ldrsb r6, [r3, r1]  // r6 = arr[j]
  ldrsb r7, [r3, r5]  // r7 = arr[j + 1]

  cmp r6, r7  // if (arr[j] <= arr[j+1]) no swap
  ble no_swap
  
  // temp variable unnecessary because arr[j], arr[j+1], j, j + 1 stored in separate registers
  strb r6, [r3, r5]  // arr[j] = arr[j + 1]
  strb r7, [r3, r1]  // arr[j + 1] = arr[j]

  no_swap:

  add r1, #1  // ++j
  b loop_j

done_j:
  add r0, #1  // ++i
  b loop_i

done: // Infinite loop when done sorting
    b done
.size main, .-main
