'''
".+"
">.+<
>.+<\w
>\s.+\s<
'''
import sys
import re


filename = str(sys.argv[1])
file = open(filename, 'r')
re_one = r'".+"'
re_two = r'">.+<'
re_three = r'>.+<\w'
re_four = r'>\s.+\s<'
to_cap = []
for line in file:
    match_one = re.search(re_one, line)
    if (match_one):
        t1 = match_one.group()
        to_cap.append(t1)
    match_two = re.search(re_two, line)
    if (match_two):
        to_cap.append(match_two.group())
    match_three = re.search(re_three, line)
    if (match_three):
        if ("href" in match_three.group()):
            t3 = re.search(re_four, match_three.group())
            to_cap.append(t3.group())
file = open(filename, 'r')
t_f = False
for l in file:
    for p in to_cap:
        if p in l:
            t_f = True
            l = l.replace(p, p.upper())
    print(l)