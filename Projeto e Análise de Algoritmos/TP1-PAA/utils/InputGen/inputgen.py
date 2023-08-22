# Script utilizado para gerar arquivos de entrada desordenados que serão utilizados pelos algoritmos
# Arquivos de entrada possuem formato *.in
# Arquivos de saída possuem formato *.out

import random, os

instance_sizes = [10,100,1000,10000,100000,1000000]
number_instances = 20

for instance in instance_sizes:
    print(f"[+] Running Instance: N{instance}")
    for number in range(1,number_instances+1):
        filename = f"../../input/n{instance}/instance-n{instance}-{number}.in"
        os.makedirs(os.path.dirname(filename), exist_ok=True)
        with open(filename, "w") as f:
            for i in range(instance):
                random_num = random.randint(0, instance)
                f.write(str(random_num) + "\n")