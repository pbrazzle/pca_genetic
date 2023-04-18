# Script to combine .csv files into a PDF of graphs

import sweeper

import os
from fpdf import FPDF
import matplotlib.pyplot as plt
import argparse

def csv_to_graph(filename):
    image_name = '.'.join(filename.split('.')[:-1])
        
    print('Reading '+filename)
    file = open(filename, 'r')
    run_data = [line.rstrip() for line in file if line != '\n']
    avg_data = [float(x.split(',')[0]) for x in run_data]
    best_data = [float(x.split(',')[1]) for x in run_data]
    file.close()
        
    plt.clf()
    plt.plot(avg_data, label='Avg Fitness')
    plt.plot(best_data, label='Best Fitness')
    plt.xlabel('Generations')
    plt.ylabel('Fitness')
    plt.title(image_name)
    plt.savefig(image_name+'.png')
    file.close()
    return image_name + '.png'

def make_graph_pdf(sweep_name='blank_sim'):
    files = [x for x in os.listdir() if x.endswith('.csv') and sweep_name in x]
    images = []
    for f in files:
        images.append(csv_to_graph(f))
        
    pdf = FPDF()
    for image in images:
        pdf.add_page()
        pdf.image(image, w=200)
        os.remove(image)
    pdf.output('sweep_'+sweep_name+'.pdf', 'F')
    
if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('sim_name', default='blank_sim')
    args = parser.parse_args()

    make_graph_pdf(args.sim_name)