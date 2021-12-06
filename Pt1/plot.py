import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


def plot_analysis(file):
    data = pd.read_csv(file)
    th_nb = data.columns[0]
    comp_time_by_th_nb = [(data.loc[data[th_nb] == x]) for x in range(2, 17)]

    ar_cmp_t = [comp_time_by_th_nb[x][comp_time_by_th_nb[x].columns[-1]] for x in range(len(comp_time_by_th_nb))]

    fig, ax = plt.subplots(figsize=(14,8))
    meanlineprops = dict(linestyle='-', linewidth=2.0, color='red')
    #ax.violinplot(ar_cmp_t)
    ax.boxplot(ar_cmp_t, showfliers=True, autorange=True, patch_artist=True, meanline=True, showmeans=True, meanprops=meanlineprops)
    plt.xticks([x for x in range(1, 16)], [x for x in range(2,17)])
    plt.xlabel("Thread Number")
    plt.ylabel("Compilation Time")
    plt.title(file[:-4].upper())
    plt.show()

    means = [float("%.5f" % ar.mean()) for ar in ar_cmp_t]
    std_dev = [float('%.5f' % ar.std()) for ar in ar_cmp_t]
    print('Moyennes respectives: \n', means)
    print()
    print("Ecarts types respectifs: \n", std_dev)



plot_analysis("../csv/philo.csv")
plot_analysis('../csv/customPhilo.csv')
plot_analysis('../csv/buffer.csv')
plot_analysis('../csv/customBuffer.csv')
plot_analysis('../csv/rw.csv')
plot_analysis('../csv/customRW.csv')

