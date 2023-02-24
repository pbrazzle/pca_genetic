import os
import matplotlib.pyplot as plt
from fpdf import FPDF
import numpy as np

class Simulation:
    def __init__(self):
        self.name = "DEFAULT"
        
        self.gen_size = 100
        self.mut_chance = 0.01
        self.mut_size = 0.01
        self.param_range = 1
        
        self.fit_calc = 'DistanceCalculator'
        self.parent_select = 'FitnessSumSelector'
        self.parent_comb = 'SingleCrossingCombiner'
        
        self.model_type = 'LinearGeneticModel'
        self.model_data = 3
        self.model_params = [0]*self.model_data**2

        self.num_training = 1
        self.training_data = [([1,1,1], [1,1,1])]
        
        self.num_gens = 1000
        
    def print_gen(self):
        gen_string = ""
        gen_string += self.name + '\n'
        gen_string += str(self.gen_size) + '\n'
        gen_string += str(self.mut_chance) + '\n'
        gen_string += str(self.mut_size) + '\n'
        gen_string += str(self.param_range) + '\n'
        gen_string += self.fit_calc + '\n'
        gen_string += self.parent_select + '\n'
        gen_string += self.parent_comb + '\n'
        gen_string += self.model_type + '\n'
        gen_string += str(self.model_data) + '\n'
        gen_string += ','.join([str(x) for x in self.model_params]) + '\n'
        gen_string += str(self.num_training) + '\n'
        for item in self.training_data:
            gen_string += ','.join([str(x) for x in item[0]]) + '\n'
            gen_string += ','.join([str(x) for x in item[1]]) + '\n'
        gen_string += str(self.num_gens)
        return gen_string

def generate_sweep_file(filename, template, sweep_vals, sweep_name, num_runs=1):
    file = open(filename, 'w')
    data_filenames = []
    for val in sweep_vals:
        run_files = []
        for i in range(num_runs):
            template.name = "sweep_"+sweep_name+'_'+str(val).replace('.','_')+'_'+str(i)
            run_files.append(template.name+'.csv')
            setattr(template, sweep_name, val)
            file.write(template.print_gen()+'\n\n')
        data_filenames.append(run_files)
    file.close()
    return data_filenames

def run_sim(filename):
    os.system('..\\bin\\GeneticSim '+filename)
    
def run_sweep(template, sweep_vals, sweep_name, num_runs=1):
    print("Sweeping " + sweep_name + " from " + str(sweep_vals[0]) + " to " + str(sweep_vals[-1]))
    filename = 'sweep_'+sweep_name+'_'+str(sweep_vals[0]).replace('.','_')+'_'+str(sweep_vals[-1]).replace('.','_')+'.gen'
    data_filenames = generate_sweep_file(filename, template, sweep_vals, sweep_name, num_runs=num_runs)
    run_sim(filename)
    os.system('del '+filename)
    return data_filenames
    
def run_sweep_with_graphs(template, sweep_vals, sweep_name, num_runs=1):
    data_filenames = run_sweep(template, sweep_vals, sweep_name, num_runs=num_runs)
    graph_filenames = []
    for f in data_filenames:
        image_name = ''
        avg = []
        best = []
        
        print('Averaging runs')
        for run in f:
            image_name = '_'.join(run.split('_')[:-1])
            print('Reading '+run)
            file = open(run, 'r')
            run_data = [line.rstrip() for line in file if line != '\n']
            avg_data = [float(x.split(',')[0])/len(f) for x in run_data]
            best_data = [float(x.split(',')[1])/len(f) for x in run_data]
            if len(avg) == 0:
                avg = [0 for x in run_data]
                best = [0 for x in run_data]
            avg = [x+y for x,y in zip(avg, avg_data)]
            best = [x+y for x,y in zip(best, best_data)]
            file.close()
            os.system('del '+run)
            
        plt.clf()
        plt.plot(avg, label='Avg Fitness')
        plt.plot(best, label='Best Fitness')
        plt.xlabel('Generations')
        plt.ylabel('Fitness')
        plt.title(image_name)
        plt.savefig(image_name)
        graph_filenames.append(image_name+'.png')
        file.close()

    pdf = FPDF()
    for graph in graph_filenames:
        pdf.add_page()
        pdf.image(graph, w=200)
        os.system('del '+graph)
    pdf.output('sweep_'+sweep_name+'_'+str(sweep_vals[0]).replace('.','_')+'_'+str(sweep_vals[-1]).replace('.','_')+'.pdf', 'F')
    
sim = Simulation()
sim.gen_size = 100
sim.num_gens = 300
sim.mut_chance = 0.1
sim.mut_size = 0.01
#sim.model_params = [1,0.1,0,0,1,0,0,0,1]
sim.param_range = 5

#run_sweep_with_graphs(sim, np.arange(0.001,0.011,0.001), 'param_range', num_runs=5)
#run_sweep_with_graphs(sim, np.arange(1,11,1), 'param_range', num_runs=5)
#run_sweep_with_graphs(sim, np.arange(0.1,0.6,0.1), 'mut_size', num_runs=5)
#run_sweep_with_graphs(sim, np.arange(0.0,0.31,0.05), 'mut_size', num_runs=1)
run_sweep_with_graphs(sim, np.arange(10, 110, 10), 'gen_size', num_runs=5)
