# group59 

## Project1  
1.实验说明：  
  在简化的生日攻击中，攻击者试图找到两个不同的输入消息，它们经过哈希函数后产生相同的哈希值。攻击者通过生成多个随机的输入消息并计算它们的哈希值，当找到两个相同的哈希值时，攻击者就成功找到了一对碰撞。
本实验使用的寻找碰撞的方法是简单的线性搜索，将数据进行SM2的相关运算后将结果存入表中，一边存表一边查表，逐一比较已计算的散列值的前四位是否与之前计算的散列值相同。如果找到相同的前四位，即表示找到了碰撞。  

2.实验环境：
   Vs2022  

3.实验结果：
![Image text](https://github.com/xymio/group59/blob/main/image/project1.png)
由于采用的线性的查表搜索，数据越大可能造成该方法不太适用。

## Project2
1.实验说明：  
由于哈希函数的输出空间远远小于输入空间，必然存在多个不同的输入映射到相同的散列值。rho攻击利用了这个性质，将哈希函数的输入空间划分为若干部分，并观察两个输入是否属于同一部分。本次实验与生日攻击相似，都是采用了查找表的方法。
实现：    
  &emsp;初始化变量 rho 和 start，准备进行rho攻击。
  &emsp;循环执行以下步骤，直到找到弱碰撞或达到最大尝试次数：  
  &emsp;a.根据 rho 的值生成一个字符串 str。   	
  &emsp;b.对 str 进行填充，得到填充值 paddingValue。  
  &emsp;c.将 paddingValue 作为输入，进行SM2加密运算得到加密结果 result。  
  &emsp;d.在之前的计算结果集合 outlist 中查找是否存在与 result 前四位相同的加密结果。   
  &emsp;e.如果找到相同结果，并且对应的输入值不同于当前的 str，则表示发生了弱碰撞。输出碰撞的相关信息并结束攻击。   
  &emsp;f. 更新计算结果集合 outlist 和输入值集合 inlist。  
  &emsp;如果循环结束仍然没有找到弱碰撞，表示rho攻击失败。  
  
2.实验环境：
  Vs2022  
3.实验结果：  
![Image text](https://github.com/xymio/group59/blob/main/image/project2.png)
  
可以得出，在寻找16bit碰撞中生日攻击所需要的时间少于rho攻击，如果加长碰撞的bit长度，rho可能有更高的效率。

## Project4  
1实验说明：  
本实验主要通过了减少多余的输出和利用编译器进行优化  
2.实验环境：  
  	VS2022  
3.实验结果  
未优化前：  
 ![Image text](https://github.com/xymio/group59/blob/main/image/project4.1.png)
减少多余的输出后并采用O1编译  
![Image text](https://github.com/xymio/group59/blob/main/image/project4.2.png)

## Project5  
1.实验说明：  
Merkle Tree是一种用于验证和快速检索大量数据完整性的数据结构。  
Merkle Tree的实现原理如下：  
&emsp;随机生成指定长度的消息块，每个消息块由6个随机生成的字母组成。  
&emsp;哈希计算：对每个叶子节点应用哈希函数，计算出其哈希值。  
&emsp;构建树结构：首先计算出默克尔树的深度，然后以输入的消息块作为叶子节点构建初始的默克尔树。接着从底部向上逐层生成默克尔树的节点，每层的节点通过对相邻节点进行哈希运算得到。如果某一层的节点数为奇数，则直接将最后一个节点加入到上一层。  
&emsp;验证函数：首先对指定元素进行哈希运算，然后检查该哈希值是否存在于默克尔树的根节点之前的叶子节点中。如果存在，则确定指定元素在消息中，并通过递归比较和组合兄弟节点的哈希值来计算出根节点的哈希值，最后将其与预期的根节点进行比较，以确定指定元素是否在默克尔树中。  
  
2.实验环境：  
  Python3.10  
3.实验结果：  

![Image text](https://github.com/xymio/group59/blob/main/image/project5.png)


## Project9
1.实验说明：  
AES: 	AES的核心就是实现一轮中的所有操作。  
&ensp;我们可以将不同轮次分为初始轮、普通轮、 最终轮。   
&emsp;初始轮它只做一个操作：轮密钥加   
&emsp;普通轮有四个操作步骤：①字节代换、②行移位、③列混淆、④轮密钥加   
&emsp;最终轮有三个操作步骤：①字节代换、②行移位、③轮密钥加   
&emsp;以128为例，AES的加密公式为C=E(K,P)，在加密函中，会执行一个轮函数，并且执行10次这个轮 数，这个轮函数的前9次执行的操作是一样的.  

SM4:	其基本原理是使用分组密码结构将输入的明文块转换为密文块，并使用相同的密钥	进行加密和解密操作。基本过程有密钥扩展包括异或、S盒替代、线性变换等运算，加	密运算进行32轮的迭代操作，最后，将最后一轮迭代后的L32和R32合并，作为加密结果输出。  
2.实验环境  
  Vs2022  
3.实验结果  

![Image text](https://github.com/xymio/group59/blob/main/image/project9.png)


## Project11
1.实验说明：  
&ensp;本实验在SM2加密过程中随机数K利用 RFC6979进行生成。  
&ensp;k的生成：首先将私钥转换为字节数组，并计算消息的哈希值。计算了整数b_len，该整数表示曲线的阶的字节长度。然后，根据RFC 6979算法的步骤，代码初始化了两个字节串v和k。v被初始化为字节串\x01的重复，而k被初始化为字节串\x00的重复。接着根据RFC 6979算法的迭代步骤：在每次迭代中，代码使用HMAC函数将k与其他参数进行哈希运算，然后更新k和v的值。迭代的最后，通过将v转换为整数来获取最终的k。最后，代码返回生成的随机数k。  
由于K的生成与SM2函数不在一个文件内，运行代码时需要先在RFC文件中生成中随机数K，再将其带入SM2的enc函数中,才能正确运行该代码。  
2.实验环境  
  Python 3.10  
3.实验结果 

![Image text](https://github.com/xymio/group59/blob/main/image/project11.png)
##  Project14
1.实验说明：  
&emsp;本实验利用SM2进行的签名和验证  
sign_sm2函数：  
   &emsp;输入参数：args（包含了椭圆曲线参数），dA（私钥），M（消息）  
   &emsp;输出：签名值（r,s）
   &emsp;生成随机数k。   
   &emsp;计算椭圆曲线点C1=[k]G，并将其转换为比特串形式。   
   &emsp;计算椭圆曲线点S = [h]C1。   
   &emsp;计算r = (e + x1) mod n，其中e是消息M的哈希值。   
   &emsp;计算s = ((1+dA)^-1 * (k-r*dA)) mod n。   
   &emsp;输出签名值（r,s）。  
verify_signature函数   
   &emsp;输入参数：args（包含了椭圆曲线参数），PA（公钥），signature，M  
   &emsp;将消息M转换为比特串形式。    
   &emsp;计算椭圆曲线点T = [s]G + [r]QA。  
   &emsp;计算x = (e + x1) mod n，比较r与x是否相等 。  
   &emsp;如果r与x不相等，则签名验证失败，否则验证通过。  
2.实验环境  
Python 3.10 
3.实验结果 
![Image text](https://github.com/xymio/group59/blob/main/image/project14.png)
## project17
只有文字分析

## Project19
1.实验说明：  
  &emsp;本次实验一个简化版本的ECDSA签名伪造函数的实现。  
  &emsp;首先，定义了一些参数：有限域F、椭圆曲线C（采用secp256k1曲线）、基点G、阶数N和P。  
  &emsp;然后，定义了一个名为forge的函数，它接受一个值c和可选的参数a作为输入。该函数用于创建一个伪造的ECDSA签名。  
  &emsp;变量c用于控制循环迭代和作为计算伪造签名的参数之一。在函数内部，a被转换为有限域N的元素，R被计算为c*G + int(a)*P，其中*表示椭圆曲线上的点的倍乘操作。接下来，计算s作为(int(R.xy()[0]))/a的模N的结果，其中int(R.xy()[0])是R的x坐标。计算m作为c*int(R.xy()[0])/a的模N的结果。  
  &emsp;即可以得到相应的伪造签名的hash1、r1和s1值。  
  &emsp;通过调整输入参数c和a，可以生成不同的伪造签名。  
2.实验环境：  
  Sagemath  
3.实验结果  
![Image text](https://github.com/xymio/group59/blob/main/image/project19.png)



&emsp;该实验可以生成不同的伪造签名，但是伪造特定人的签名还需要进一步进行签名验证等工作。

## Group59 李婧萱 202100460103


