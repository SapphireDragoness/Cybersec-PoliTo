# RSA attacks

## How RSA works

1. Randomly generate two prime numbers of the same size, $p$ and $q$
2. Let $N = pq$: $N$ is the RSA modulus
3. Let $\phi(N)=(p-1)(q-1)$
4. Let $e$ and $d$ be two integers satisfying $ed=1\mod\phi(N)$: $e$ is the public exponent and $d$ is the private exponent
5. The pair $(N,e)$ is the public key, while the pair $(N,d)$ is the private key

A message $M$ is encrypted by computing $C=M^e\mod N$.
An encrypted message $C$ is decrypted by computing $M=C^d\mod N$.

## Attacks

### Factorization

Brute force attack. Possible if $N$ is easily factorizable: $p$ and $q$ are "small", $N$ has a known decomposition.

#### Fermat's factorization

Works if $p$ and $q$ are close to each other:

1. $p=a+b$ and $q=a-b$
2. For some integer $a$, if $b$ is small, then the modulus becomes $N$=pq=(a+b)(a-b)=a^2-b^2$
3. Start Fermat's factorization algorithm from the midpoint: $a=b=\sqrt(N)$
4. Increase $a$ at each step and the recompute $b$
5. Stop when $b=\sqrt(a^2-n)$ is found

### Common prime

If $N_1$ and $N_2$ have a common prime:

- $N_1=p*q_1$
- $N_2=p*q_2$
It is possible to use Euclid's algorithm to factorize $N_1$ and $N_2$:

1. $\gcd(N_1,N_2)=p$
2. $q_1=N_1//p$
3. $q_2=N_2//q_1$

### Common modulus

If two keys have a common modulus:

- $k_1=(e_1,N)$
- $k_2=(e_2,N)$
and the same message $M$ is encrypted with both $k_1$ and $k_2$:
- $C_1=M^{e_1}\mod(N)$
- $C_2=M^{e_2}\mod(N)$
It is possible to use Bézout's identity to find: $e_1*u+e_2*v=\gcd(e_1,e_2)$
If $(e_1,e_2)=1$, then $C_1^u*C_2^v=M^{e_1*u+e_2*v}=M\mod(N)$

### Low public exponent

If $e=3$ and the message $M$ to encrypt satisfies the following properties:

- $C=M^e<n$
- $M*M*M<n$
Then $M$ is the integer cubic root of the ciphertext $C$ ($M=C^3\mod(N)$)

### Hastad's broadcast

If the same message $M$ is encrypted with different public keys, each using different moduli but with the same exponent $e=3$, and at least $e$ ciphertexts are known, it is possible to decrypt the message. For all $i<e$:

- compute $N_i=N//n_i$
- find Bézout coefficients $u_i,v_i$: $N_i*u_i+n_i*v_i=1$
- a possible solution is: $C=C_1*u_i*N_i+\dots+C_e*u_e*N_e$

### LSB oracle

The LSB oracle returns the last bit of the decrypted result, or wheter the last bit is even or odd. It is known that:

- $N$ is odd
- $2M$ is even

So:

- if $2M<N$, the result is even (no modulo operation happens)
- if $2M>N$, the result is odd because $N$ is odd

By sending $2M$ ($C'=2^eC=2^eM^e=(2M)^e$) to the oracle, it is possible to deduce whether $2M$ is lower or higher than $N$. If $n$ is the size in bits of the modulus, the ciphertext can be decrypted in $\log(n)$ requests (by each time multiplying $M$ by two and sending it).

### Low private exponent

If the private exponent is low, it can be recovered from the public key. $d$ is considered low when:

- $N^{0.25}$ if Wiener's attacks is used
- $N^{0.292}$ if Boneh-Durfee is used

### Coppersmith's short pad

Given a message $M$, padded with two random values $r_1$ and $r_2$ composed of at most $p$ bits:

- $M_1=M||r_1\leftarrow C_1=M_1^e\mod N$
- $M_2=M||r_2\leftarrow C_2=M_2^e\mod N$

An attacker accessing the public key can efficiently recover $M$ if $p<\lfloor N/e^2\rfloor$.
