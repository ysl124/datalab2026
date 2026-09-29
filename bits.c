/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~((~x) | (~y));
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return (~(x & y)) & ~((~x) & (~y));
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    int a=x>>31;
    int b=y>>31;
    int c=!(x && y);
    if(c && (x ^ b)) return 0;
    if(c && (a ^ y)) return 0;
    return !(a ^ b);
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */

//寻找最高位1的位置
int logtwo(int v) {
    int pos = 0;//记录最高位1的位置
    int n = 0;
    n = ((v >> 16) > 0) << 4; //判断最高的16位里面有没有1
    v = v >> n;
    pos |= n;

    n = ((v >> 8) > 0) << 3;
    v = v >> n;
    pos |= n;

    n = ((v >> 4) > 0) << 2;
    v = v >> n;
    pos |= n;

    n = ((v >> 2) > 0) << 1;
    v = v >> n;
    pos |= n;

    n = (v >> 1) > 0;
    v = v >> n;
    pos |= n;
    
    return pos;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */

//构建掩码，提取对应位置的数据，相加
int byteSwap(int x, int n, int m) {
    int count1=n<<3, count2=m<<3;
    int mask1=0xFF<<(count1);
    int mask2=0xFF<<(count2);
    int temp1=x & mask1;
    int temp2=x & mask2;
    int mask3=~(mask1|mask2);
    int temp3=x & mask3;
    temp1=temp1>>(count1)<<(count2)& mask2;
    temp2=temp2>>(count2)<<(count1)& mask1;
    return temp1|temp2|temp3;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse() = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    //一位一位移动，相加(并集)
    unsigned r = 0;
    int i=32;
    while(i--)
    {
        r = r | (((v >> (i-1)) & 1) << (32 - i));
    }
    return r;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    // C语言中>>为算数右移
    /*
    先做算术右移：x >> n。
    构造一个与 n 相关的掩码：高 n 位全是 0，低 32-n 位全是 1
    按位与（&）：(x >> n) & mask。
    */
    //“int mask = ~((1 << 31) >> (n-1))”使用了非法的运算符- 以及 n=0会报错
    int mask = ~(((1 << 31) >> n) << 1);
    return (x >> n) & mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int answer = 0;
    int n = 0;
    n = !(~(x >> 16)); //判断最高的16位是否都是1
    answer += n << 4;
    x = x << (n << 4);

    n = !(~(x >> 24));
    answer += n << 3;
    x = x << (n << 3);

    n = !(~(x >> 28));
    answer += n << 2;
    x = x << (n << 2);

    n = !(~(x >> 30));
    answer += n << 1;
    x = x << (n << 1);

    answer += (x >> 31) & 1; //最高位
    answer += ((x >> 31) & 1) & ( (x >> 30) & 1) ;//次高位

    return answer;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */

/* 
提取符号为s
找到非符号位的最高位的1的位置n，得到frac（处理舍入问题）
n+=127得到exp
*/

unsigned float_i2f(int x) {
    if(x == 0) return 0;
    int s = x & 0x80000000;
    if(s) x=-x;

    int n = 31;
    while(!(x >> n)) n--;

    int exp = (n+127)<<23;
    unsigned frac = 0; 

    if(n>23){
        unsigned lost = x & ((1 << (n - 23)) - 1);
        frac = x>>(n-23) & 0x7fffff;

        unsigned half = 1 << (n-24);
        if (lost > half) {
            frac++;                   
        } else if (lost == half) {
            if (frac & 1) frac++;     
        }
        
        if (frac >> 23) {
            frac = 0;
            exp += 0x800000;        
        }
    } 
    else {
        frac = (x << (23 - n)) & 0x7FFFFF;
    }
    return s+exp+frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned exp = (uf >> 23) & 0xFF;

    if(exp == 0xFF) return uf;
    else if(exp == 0){
        return (uf & 0x80000000) + (uf << 1);
    }
    else{
        return uf + (1 << 23);
    }
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned s = uf2 >> 31;
    unsigned exp = (uf2 >> 20) & 0x7ff;
    int e = exp - 1023;

    if(e < 0) return 0;
    else if(e >= 31) return 0x80000000;
    else{
        unsigned f1 = (uf2 & 0xfffff) + 0x100000;
        unsigned f2 = uf1;
        // 需要舍弃的小数位 
        unsigned shift = 52 - e; 
        unsigned result;
    
        if (shift >= 32) {
            result = f1 >> (shift - 32);         
        } 
        else {
            result = (f1 << (32 - shift)) | (f2 >> shift);
        }
        
        if (s) return -result;
        return result;
    }
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x >= 128) {
        return 0x7F800000; 
    }
    
    if (x <= -127) {
        if (x >= -149) {
            return 1 << (x + 149);
        }
        return 0; 
    }
    return (x + 127) << 23;
}
