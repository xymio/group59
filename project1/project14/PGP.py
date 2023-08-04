
from hashlib import sha256
import random
from math import gcd, ceil, log
from gmssl import sm3
import gmssl

from hashlib import sha256
from ecdsa.util import string_to_number, number_to_string
import hmac




# 数据类型装换
# 整数到字节串的转换。接收非负整数x和字节串的目标长度k，k满足2^8k > x。返回值是长为k的字节串。k是给定的参数。
def int_to_bytes(x, k):         # 整体思路是先左填充0将x变为k*8位16进制数串，再每2位合成1个字节
    if pow(256, k) <= x:
        raise Exception("无法实现整数到字节串的转换，目标字节串长度过短！")
    s = hex(x)[2:].rjust(k*2, '0')          # s是k*2位十六进制串
    M = b''
    for i in range(k):
        M = M + bytes([eval('0x' + s[i*2:i*2+2])])
    return M


# 字节串到整数的转换。接受长度为k的字节串。返回值是整数x
def bytes_to_int(M):            # 整体思路是从后向前遍历M，每个字节的基数是2^8。
    k = len(M)          # k是字节串的长度
    x = 0           # x存储最后的整数
    for i in range(k-1, -1, -1):
        x += pow(256, k-1-i) * M[i]
    return x


# 比特串到字节串的转换。接收长度为m的比特串s。返回长度为k的字节串M。其中k = [m/8] 向上取整。
def bits_to_bytes(s):           # 先判断字符串整体是否能正好转换为字节串，即长度是否为8的倍数。若不是则左填充至长度为8的倍数。
    k = ceil(len(s)/8)          # 比特串长度除以8向上取整
    s = s.rjust(k*8, '0')           # 若能整除这一步相当于没有，若不能则相当于将其左填充为长度能被8整除得k
    M = b''         # M存储要返回的字节串
    for i in range(k):
        M = M + bytes([eval('0b' + s[i*8: i*8+8])])
    return M


# 字节串到比特串的转换。接收长度为k的字节串M，返回长度为m的比特串s，其中m = 8k。字节串逐位处理即可。
def bytes_to_bits(M):           # 整体思路是把每个字节变为8位比特串，用列表存储，最后连接起来
    s_list = []
    for i in M:
        s_list.append(bin(i)[2:].rjust(8, '0'))         # 每次循环存储1个字节。左填充补0
    s = ''.join(s_list)
    return s


# 域元素到字节串的转换。域元素是整数，转换成字节串要明确长度。文档规定域元素转换为字节串的长度是ceil(ceil(log(q, 2)/8))。接收的参数是域元素a，返回字节串M
def fielde_to_bytes(e):
    q = eval('0x' + '8542D69E 4C044F18 E8B92435 BF6FF7DE 45728391 5C45517D 722EDB8B 08F1DFC3'.replace(' ', ''))
    t = ceil(log(q, 2))
    l = ceil(t / 8)
    return int_to_bytes(e, l)


# 字节串到域元素的转换。直接调用bytes_to_int()。接收的参数是字节串M，返回域元素a
def bytes_to_fielde(M):         # 域元素不用填充
    return bytes_to_int(M)


# 域元素到整数的转换
def fielde_to_int(a):           # 直接返回
    return a


# 点到字节串的转换。接收的参数是椭圆曲线上的点p，元组表示。输出字节串S。选用未压缩表示形式
def point_to_bytes(P):
    xp, yp = P[0], P[1]
    x = fielde_to_bytes(xp)
    y = fielde_to_bytes(yp)
    PC = bytes([0x04])
    s = PC + x + y
    return s


# 字节串到点的转换。接收的参数是字节串s，返回椭圆曲线上的点P，点P的坐标用元组表示
def bytes_to_point(s):
    if len(s) % 2 == 0:
        raise Exception("无法实现字节串到点的转换，请检查字节串是否为未压缩形式！")
    l = (len(s) - 1) // 2
    PC = s[0]
    if PC != 4:
        raise Exception("无法实现字节串到点的转换，请检查PC是否为b'04'！")
    x = s[1: l+1]
    y = s[l+1: 2*l+1]
    xp = bytes_to_fielde(x)
    yp = bytes_to_fielde(y)
    P = (xp, yp)            # 此处缺少检验点p是否在椭圆曲线上
    return P


# 附加数据类型转换
# 域元素到比特串
def fielde_to_bits(a):
    a_bytes = fielde_to_bytes(a)
    a_bits = bytes_to_bits(a_bytes)
    return a_bits


# 点到比特串
def point_to_bits(P):
    p_bytes = point_to_bytes(P)
    p_bits = bytes_to_bits(p_bytes)
    return p_bits


# 整数到比特串
def int_to_bits(x):
    x_bits = bin(x)[2:]
    k = ceil(len(x_bits)/8)         # 8位1组，k是组数。目的是方便对齐
    x_bits = x_bits.rjust(k*8, '0')
    return x_bits


# 字节串到十六进制串
def bytes_to_hex(m):
    h_list = []         # h_list存储十六进制串中的每一部分
    for i in m:
        e = hex(i)[2:].rjust(2, '0')            # 不能把0丢掉
        h_list.append(e)
    h = ''.join(h_list)
    return h


# 比特串到十六进制
def bits_to_hex(s):
    s_bytes = bits_to_bytes(s)
    s_hex = bytes_to_hex(s_bytes)
    return s_hex


# 十六进制串到比特串
def hex_to_bits(h):
    b_list = []
    for i in h:
        b = bin(eval('0x' + i))[2:].rjust(4, '0')           # 增强型for循环，是i不是h
        b_list.append(b)
    b = ''.join(b_list)
    return b


# 十六进制到字节串
def hex_to_bytes(h):
    h_bits = hex_to_bits(h)
    h_bytes = bits_to_bytes(h_bits)
    return h_bytes


# 域元素到十六进制串
def fielde_to_hex(e):
    h_bytes = fielde_to_bytes(e)
    h = bytes_to_hex(h_bytes)
    return h


# 密钥派生函数KDF。接收的参数是比特串Z和要获得的密钥数据的长度klen。返回klen长度的密钥数据比特串K
def KDF(Z, klen):
    v = 256           # 密码杂凑函数采用SM3
    if klen >= (pow(2, 32) - 1) * v:
        raise Exception("密钥派生函数KDF出错，请检查klen的大小！")
    ct = 0x00000001
    if klen % v == 0:
        l = klen // v
    else:
        l = klen // v + 1
    Ha = []
    for i in range(l):         # i从0到 klen/v-1（向上取整）,共l个元素
        s = Z + int_to_bits(ct).rjust(32, '0')         # s存储 Z || ct 的比特串形式 # 注意，ct要填充为32位
        s_bytes = bits_to_bytes(s)          # s_bytes存储字节串形式
        s_list = [i for i in s_bytes]
        hash_hex = sm3.sm3_hash(s_list)
        hash_bin = hex_to_bits(hash_hex)
        Ha.append(hash_bin)
        ct += 1
    if klen % v != 0:
        Ha[-1] = Ha[-1][:klen - v*(klen//v)]
    k = ''.join(Ha)
    return k


# 模逆算法。返回M模m的逆。在将分式模运算转换为整数时用，分子分母同时乘上分母的模逆。
def calc_inverse(M, m):
    if gcd(M, m) != 1:
        return None
    u1, u2, u3 = 1, 0, M
    v1, v2, v3 = 0, 1, m
    while v3 != 0:
        q = u3 // v3
        v1, v2, v3, u1, u2, u3 = (u1 - q * v1), (u2 - q * v2), (u3 - q * v3), v1, v2, v3
    return u1 % m


# 将分式模运算转换为整数。输入 up/down mod m, 返回该分式在模m意义下的整数。点加和二倍点运算时求λ用。
def frac_to_int(up, down, p):
    num = gcd(up, down)
    up //= num
    down //= num         # 分子分母约分
    return up * calc_inverse(down, p) % p


# 椭圆曲线上的点加运算。接收的参数是元组P和Q，表示相加的两个点，p为模数。返回二者的点加和
def add_point(P, Q, p):
    if P == 0:
        return Q
    if Q == 0:
        return P
    x1, y1, x2, y2 = P[0], P[1], Q[0], Q[1]
    e = frac_to_int(y2 - y1, x2 - x1, p)            # e为λ
    x3 = (e*e - x1 - x2) % p            # 注意此处也要取模
    y3 = (e * (x1 - x3) - y1) % p
    ans = (x3, y3)
    return ans


# 二倍点算法。不能直接用点加算法，否则会发生除零错误。接收的参数是点P，素数p，椭圆曲线参数a。返回P的二倍点。
def double_point(P, p, a):
    if P == 0:
        return P
    x1, y1 = P[0], P[1]
    e = frac_to_int(3 * x1 * x1 + a, 2 * y1, p)         # e是λ
    x3 = (e * e - 2 * x1) % p         # 取模！！！！！
    y3 = (e * (x1 - x3) - y1) % p
    Q = (x3, y3)
    return Q


# 多倍点算法。通过二进制展开法实现。接收的参数[k]p是要求的多倍点，m是模数，a是椭圆曲线参数。
def mult_point(P, k, p, a):
    s = bin(k)[2:]# s是k的二进制串形式
    Q = 0
    for i in s:
        Q = double_point(Q, p, a)
        if i == '1':
            Q = add_point(P, Q, p)
    return Q


# 验证某个点是否在椭圆曲线上。接收的参数是椭圆曲线系统参数args和要验证的点P(x, y)。
def on_curve(args, P):
    p, a, b, h, G, n = args
    x, y = P
    if pow(y, 2, p) == ((pow(x, 3, p) + a*x + b) % p):
        return True
    return False

def ModInverse(a, m):
    if m == 1:
        return 0

    def extendedEuclidean(a, b):
        if b == 0:
            return a, 1, 0
        else:
            d, x, y = extendedEuclidean(b, a % b)
            return d, y, x - (a // b) * y

    gcd, x, y = extendedEuclidean(a, m)
    if gcd != 1:
        raise ValueError("The given number does not have a modular inverse.")
    else:
        return x % m

def sign_sm2(args, dA, M):
    p, a, b, h, G, n = args  # 序列解包
    M_bytes = bytes(M, encoding='ascii')
    print("A1：用随机数发生器产生随机数k∈[1,n-1]")
    k = random.randint(1, n-1)
    k_hex = hex(k)[2:]  # k_hex 是k的十六进制串形式
    print("生成的随机数是：", k_hex)

    print("\nA2:计算椭圆曲线点C1=[k]G=(x1,y1)，将C1的数据类型转换为比特串")
    C1 = mult_point(G, k, p, a)
    print("椭圆曲线点C1=[k]G=(x1,y1)的坐标是:", tuple(map(hex, C1)))
    C1_bits = point_to_bits(C1)
    print("椭圆曲线点C1=[k]G=(x1,y1)的坐标的比特串形式是:", C1_bits)

    print("\nA3：计算椭圆曲线点S = [h]C1")
    S = mult_point(G, h, p, a)
    if S == (float('inf'), float('inf')):
        raise Exception("计算得到的S是无穷远点")
    print("A3椭圆曲线点S = [h]C1的坐标是:", tuple(map(hex, S)))

    print("\nA4：计算椭圆曲线点r = (e+x1) mod n，若r为0或者r+k=n，则返回A1")
    sha256_hash = sha256(M_bytes).digest()
    e = int.from_bytes(sha256_hash, 'big')

    x1 = C1[0]
    r = (e + x1) % n
    if r == 0 or r + k == n:
        raise Exception("计算得到的r为0或者r+k=n，请重新选择随机数k")
    print("计算得到的r是:", hex(r)[2:])

    print("\nA5：计算s = ((1+dA)^-1 * (k-r*dA)) mod n，若s为0，则返回A1")
    s = (ModInverse(1 + int(dA,16), n) * (k - r * int(dA,16))) % n
    if s == 0:
        raise Exception("计算得到的s是0，请重新选择随机数k")
    print("计算得到的s是:", hex(s)[2:])

    print("\nA6：输出签名值（r,s）")
    signature = (r, s)
    print("签名值（r,s）是:", signature)

    return signature

def verify_signature(args, PA,signature,M):

  
    p, a, b, h, G, n = args
    r, s = signature
    M_bytes = bytes(M, encoding='ascii')

    print("B1：将消息M的数据类型转换为比特串")
    e = int.from_bytes(sha256(M_bytes).digest(), 'big')

    print("B2：计算椭圆曲线点T = [s]G + [r]QA")
    T = add_point(mult_point(G, s, p, a), mult_point(PA, r, p, a), p)
    if T == (float('inf'), float('inf')):
        raise Exception("计算得到的点T是无穷远点")
    print("椭圆曲线点T = [s]G + [r]QA 的坐标是:", tuple(map(hex, T)))

    print("B3：计算椭圆曲线点x = (e + x1) mod n，比较r与x是否相等")
    x1 = T[0]
    x = (e + x1) % n
    print("B4:x=",x)
    
    if r != x:
        print("签名验证通过")
    else:
        print("签名验证失败")





# 椭圆曲线系统参数args(p, a, b, h, G, n)的获取。
def get_args():
    p = eval('0x' + '8542D69E 4C044F18 E8B92435 BF6FF7DE 45728391 5C45517D 722EDB8B 08F1DFC3'.replace(' ', ''))
    a = eval('0x' + '787968B4 FA32C3FD 2417842E 73BBFEFF 2F3C848B 6831D7E0 EC65228B 3937E498'.replace(' ', ''))
    b = eval('0x' + '63E4C6D3 B23B0C84 9CF84241 484BFE48 F61D59A5 B16BA06E 6E12D1DA 27C5249A'.replace(' ', ''))
    h = 1
    xG = eval('0x' + '421DEBD6 1B62EAB6 746434EB C3CC315E 32220B3B ADD50BDC 4C4E6C14 7FEDD43D'.replace(' ', ''))
    yG = eval('0x' + '0680512B CBB42C07 D47349D2 153B70C4 E5D7FDFC BFA36EA1 A85841B9 E46E09A2'.replace(' ', ''))
    G = (xG, yG)            # G 是基点
    n = eval('0x' + '8542D69E 4C044F18 E8B92435 BF6FF7DD 29772063 0485628D 5AE74EE7 C32E79B7'.replace(' ', ''))
    args = (p, a, b, h, G, n)           # args是存储椭圆曲线参数的元组。
    return args


# 密钥获取。本程序中主要是消息接收方B的公私钥的获取。
def get_key():
    xB = eval('0x' + '435B39CC A8F3B508 C1488AFC 67BE491A 0F7BA07E 581A0E48 49A5CF70 628A7E0A'.replace(' ', ''))
    yB = eval('0x' + '75DDBA78 F15FEECB 4C7895E2 C1CDF5FE 01DEBB2C DBADF453 99CCF77B BA076A42'.replace(' ', ''))
    PB = (xB, yB)           # PB是B的公钥
    dB = eval('0x' + '1649AB77 A00637BD 5E2EFE28 3FBF3535 34AA7F7C B89463F2 08DDBC29 20BB0DA0'.replace(' ', ''))
    # dB是B的私钥
    key_B = (PB, dB)
    return key_B


print("SM2椭圆曲线公钥密码算法".center(100, '='))
print("本算法采用256位素数域上的椭圆曲线。椭圆曲线方程为：")
print("y^2 = x^3 + ax + b")

print("此为算法第1部分，获取相关数据".center(100, '='))
# 这里作为后续加解密算法参数的是元组args和key_B，ascii字符串明文消息M。均为不可变序列。在这一部分用于输出时不会改变其值
print("下面获取椭圆曲线系统参数")
args = get_args()           # 获取椭圆曲线系统参数
p, a, b, h, G, n = args         # 序列解包
p, a, b, h, xG, yG, n = tuple(map(lambda a: hex(a)[2:], (p, a, b, h, G[0], G[1], n)))   # 将参数转换为十六进制串便于输出
print("椭圆曲线系统所在素域的p是：", p)
print("椭圆曲线系统的参数a是：", a)
print("椭圆曲线系统的参数b是：", b)
print("椭圆曲线系统的余因子h是：", h)
print("椭圆曲线系统的基点G的横坐标xG是：", xG)
print("椭圆曲线系统的基点G的纵坐标yG是：", yG)

print("下面获取接收方B的公私钥")
key_B = get_key()           # 设置消息接收方的公私钥
PB, dB = key_B          # 序列解包，PB是公钥，是以元组形式存储的点(xB, yB), dB是私钥，是整数
xB, yB, dB = tuple(map(lambda a: hex(a)[2:], (PB[0], PB[1], dB)))
print("接收方B的公钥PB的横坐标xB是：", xB)
print("接收方B的公钥PB的纵坐标yB是：", yB)
print("接收方B的私钥dB是：", dB)
print("下面获取明文")
M = input('请输入要签名的消息(明文应为ascii字符组成的字符串)：')
print("获取的ascii字符串消息是：", M)
print("此为算法第2部分，签名部分".center(100, '='))
signature= sign_sm2(args, dB, M)            # 加密算法的参数是椭圆系统参数，B的公钥PB，ascii字符串形式的明文消息M。返回十六进制串形式的密文消息

print("此为算法第3部分，验证部分".center(100, '='))
verify_signature(args, PB, signature, M)           # 解密算法的参数是椭圆曲线系统参数，B的私钥dB，十六进制串形式的密文消息。返回ascii字符串形式的明文消息M


