#定义参数
F = FiniteField (0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F)
C = EllipticCurve ([F (0), F (7)])#secp256k1曲线
G = C.lift_x(0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798)
N = FiniteField (C.order())
P = P=-C.lift_x(0x11db93e1dcdb8a016b49840f8c53bc1eb68a382e97b1482ecad7b148a6909a5c) # block 9 coinbase payout key.

def forge(c, a=-1):  # 创建一个伪造的ECDSA签名
  a = N(a)
  R = c*G + int(a)*P
  s = N(int(R.xy()[0]))/a
  m = N(c)*N(int(R.xy()[0]))/a
  print ('hash1 = %d'%m)
  print ('r1 = %d'%(int(R.xy()[0])))
  print ('s1 = %d'%s )

for c in range(1,10):
  forge(c)
