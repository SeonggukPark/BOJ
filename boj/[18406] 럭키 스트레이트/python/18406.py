def sol():
    data = input()
    left = 0
    right = 0

    for i in range(int(len(data) / 2)):
        left += int(data[i])

    for j in range(int(len(data) / 2), len(data)):
        right += int(data[j])

    if left == right:
        print("LUCKY")
        return

    print("READY")
    

if __name__ == '__main__':
    sol()