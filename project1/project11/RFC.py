
from hashlib import sha256
from ecdsa.util import string_to_number, number_to_string
import hmac

def generate_k(private_key, message, curve_order):
    # 将私钥转换为字节数组
    private_key_bytes = number_to_string(private_key, curve_order)

    # 计算消息的哈希值
    message_hash = sha256(message).digest()

    # 定义辅助函数
    def bits2int(bits):
        return string_to_number(bits) % curve_order

    def int2octets(x):
        x_str = hex(x)[2:].rstrip('L')
        if len(x_str) & 1:
            x_str = '0' + x_str
        return bytes.fromhex(x_str)

    def H(msg):
        return sha256(msg).digest()

    # 计算整数 b 的字节长度
    b_len = int((curve_order.bit_length() + 7) / 8)

    # 根据 RFC 6979 算法计算 v
    v = b'\x01' * b_len

    # 根据 RFC 6979 算法计算 k
    k = b'\x00' * b_len

    k = hmac.new(k, v + b'\x00' + private_key_bytes + message_hash, sha256).digest()
    v = hmac.new(k, v, sha256).digest()
    k = hmac.new(k, v + b'\x01' + private_key_bytes + message_hash, sha256).digest()
    v = hmac.new(k, v, sha256).digest()

    k = bits2int(v)

    return k



private_key =0x1649ab77a00637bd5e2efe283fbf353534aa7f7cb89463f208ddbc2920bb0da0
message = b"lijingxuan"  
curve_order =0x8542d69e4c044f18e8b92435bf6ff7dd297720630485628d5ae74ee7c32e79b7 

k = generate_k(private_key, message, curve_order)
print("Generated k value:", k)
