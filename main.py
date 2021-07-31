from subprocess import call
import random

# define isQR


def isQR(x, p):
    q = (p - 1) / 2
    return pow(x, q, p)

# define findQNR


def findQNR(p):
    r = random.randint(1, p - 1)
    while isQR(r, p) == 1:
        r = random.randint(1, p - 1)
    return r

# define findQR


def findQR(p):
    r = random.randint(1, p - 1)
    return pow(r, 2, p)


# Generate the key from Keygen.c
print("Generating the key...")
call(["gcc", "-o", "keygen", "key/keygen.c", "-lgcrypt"])
call(["gcc", "-o", "encrypt", "key/encrypt.c", "-lgcrypt"])
call("key/keygen")

p = int(open("./p").read(), 16)
y = int(open("./y").read(), 16)

wrong = 0
runs = 1000
# experiment running
print("Running the experiment...")

for i in range(runs):
    pk = y

    plaintexts = dict()
    plaintexts[0] = findQNR(p)
    plaintexts[1] = findQR(p)

    challenge_bit = random.randint(0, 1)
    challenge_string = hex(plaintexts[challenge_bit])
    challenge_string = challenge_string[2:-1]
    challenge_string = challenge_string.zfill(256)
    challenge_string = challenge_string.upper()
    open("./pt", "wb").write(challenge_string)

    call("key/encrypt")
    ct_a = int(open("./ct_a").read(), 16)
    ct_b = int(open("./ct_b").read(), 16)

    output = -1

    if ((isQR(pk, p) == 1) or (isQR(ct_a, p) == 1)):
        if isQR(ct_b, p) == 1:
            output = 1
        else:
            output = 0
    else:
        if isQR(ct_b, p) == 1:
            output = 0
        else:
            output = 1

    if output != challenge_bit:
        wrong = wrong + 1
# output
print("Number of times the guess was wrong (should be 50% if this shit is secure):"), wrong, "/", runs
