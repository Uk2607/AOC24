import sys

sys.setrecursionlimit(10**6)
infile = sys.argv[1] if len(sys.argv)>=2 else 'input/06.in'

p1=0
p2=0
D = open(infile).read().strip()

G=D.split('\n')
R=len(G)
C=len(G[0])

for r in range(R):
    for c in range(C):
        if G[r][c] == '^':
            sr, sc = r, c

for o_r in range(R):
    for o_c in range(C):
        r, c = sr, sc
        d = 0
        SEEN1 = set()
        SEEN2 = set()
        while(True):
            if (r, c, d) in SEEN2:
                p2+=1
                break
            SEEN1.add((r, c))
            SEEN2.add((r, c, d))
            dr, dc = [(-1,0), (0,1), (1,0), (0,-1)][d]
            rr = r+dr
            cc = c+dc
            if not (0<=rr<R and 0<=cc<C):
                if G[o_r][o_c]=='#':
                    p1 = len(SEEN1)
                break
            if G[rr][cc]=='#' or rr==o_r and cc==o_c:
                d=(d+1)%4
            else:
                r=rr
                c=cc

print("PART1:", p1)
print("PART2:", p2)
