import os
import matplotlib.pyplot as plt
from fpdf import FPDF
import numpy as np
import random

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
  
# Training Data JSON
  
def make_vector_json(data=[]):
    return '[' + ','.join([str(x) for x in data]) + ']'
    
def make_output_selection(index=0):
    data = [0]*10
    data[index] = 1
    return '{' + 'typename : \"ModelOutputDataVector\", data : ' + make_vector_json(data) + '}'
    
def make_input_file(filename):
    return '{' + 'typename : \"ModelInputImage\", data : {filename : ' + filename + '}}'
    
def make_tdata_entry(input="null", output="null"):
    return '{' + 'input : {0}, output : {1}'.format(input, output) + '}'
    
def make_image_tdata(filename, selection):
    return make_tdata_entry(make_input_file(filename), make_output_selection(selection))
   
def get_image_dir(digit, image_num):
    return '"' + os.path.abspath(os.path.join(os.getcwd(), os.pardir)) + '\\data\\digit_training\\' + str(digit) + '\\img_' + str(image_num) + '.jpg' + '"'

def select_images_from_dir(path, num_images=1):
    all_images = os.listdir(path)
    return random.sample(all_images, num_images)
    
def build_equal_training_data(num_images=1):
    t_data = []
    for i in range(10):
        abs_path = os.path.abspath(os.path.join(os.getcwd(), os.pardir)) + '\\data\\digit_training\\' + str(i) + '\\'
        image_list = select_images_from_dir(abs_path, num_images)
        t_data = t_data + [make_image_tdata('"'+abs_path+x+'"', i) for x in image_list]
    return '[' + ','.join(t_data) + ']'
   
# Algorithm JSON
    
def make_null_abstract(typename="null"):
    return '{' + "typename : \"{0}\", data : null".format(typename) + '}'

def make_alg_json(generationSize="1", offset="0.01", mutChance="0.1", mutSize="0.01", elitism="0.05",
                    fCalc="null", pSelect="null", pComb="null"):
    return '{' + ("generationSize : {0}, offsetSize : {1}, mutationChance : {2},"
            "mutationSize : {3}, elitism : {4}, FitnessCalculator : {5},"
            "ParentSelector : {6}, ParentCombiner: {7}"
            ).format(generationSize, offset, mutChance, mutSize, elitism, fCalc, pSelect, pComb) + '}'
            
def build_basic_alg():
    fcalc = make_null_abstract("DecisionCalculator")
    pselect = make_null_abstract("FitnessSumSelector")
    pcomb = make_null_abstract("SingleCrossingCombiner")
    return make_alg_json(generationSize="100", fCalc=fcalc, pSelect=pselect, pComb=pcomb)
  
class Algorithm:
    def __init__(self):
        self.generationSize = 100
        self.offset = 1.0
        self.mutChance = 0.05
        self.mutSize = 0.01
        self.elitism = 0.05
        self.fCalc = make_null_abstract("DecisionCalculator")
        self.pSelect = make_null_abstract("FitnessSumSelector")
        self.pComb = make_null_abstract("SingleCrossingCombiner")
            
    def to_json(self):
        return '{' + ("generationSize : {0}, offsetSize : {1}, mutationChance : {2},"
            "mutationSize : {3}, elitism : {4}, FitnessCalculator : {5},"
            "ParentSelector : {6}, ParentCombiner: {7}"
            ).format(self.generationSize, self.offset, self.mutChance, self.mutSize, self.elitism, self.fCalc, self.pSelect, self.pComb) + '}'
  
# Model JSON
    
def build_nn():
    layerStr = "[" + str(28*28) + ',' + str(10) + ']'
    weightStr = "[" + ','.join(["0.0" for x in range(28*28*10)]) + ']'
    dataStr = "{" + "layer_sizes: {0}, weights: {1}".format(layerStr, weightStr) + "}"
    typeStr = "\"NeuralModel\""
    nnStr = "{" + "typename : {0}, data : {1}".format(typeStr, dataStr) + "}"
    return nnStr
    
# Simulation JSON
    
def make_sim_json(name="\"blank_sim\"", generations="1", alg="null", trainingData="null", model="null"):
    return '{' + "name : {0}, generations : {1}, algorithm : {2}, model_template : {3}, training_data : {4}".format(name, generations, alg, model, trainingData) + '}'
    
def generate_sweep_files(sweep_name, var_name, sweep_vals, alg):
    filenames = []
    for val in sweep_vals:
        setattr(alg, var_name, val)
        sim_name = sweep_name + '_' + str(val)
        sim_json = make_sim_json('"'+sim_name+'"', "10", alg.to_json(), build_equal_training_data(1), build_nn())
        json_file = open(sim_name+'.json', 'w+')
        filenames.append(sim_name+'.json')
        json_file.write(sim_json)
        json_file.close()
    return filenames
        
def run_sweep(sweep_name, var_name, sweep_vals, alg):
    files = generate_sweep_files(sweep_name, var_name, sweep_vals, alg)
    for f in files:
        os.system("..\\bin\\GeneticSim " + f)
    return ['.'.join(x.split('.')[:-1]) + '.csv' for x in files]
    
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
    
def run_sweep_with_graphs(sweep_name, var_name, sweep_vals, alg):
    files = run_sweep(sweep_name, var_name, sweep_vals, alg)
    images = []
    for f in files:
        images.append(csv_to_graph(f))
        
    pdf = FPDF()
    for image in images:
        pdf.add_page()
        pdf.image(image, w=200)
        os.system('del '+image)
    pdf.output('sweep_'+sweep_name+'_'+str(sweep_vals[0])+'_'+str(sweep_vals[-1])+'.pdf', 'F')
    
# Prebuilt Sims
    
def build_basic_nn_sim():
    nameStr = "\"basic_nn\""
    generationStr = "100"
    algStr = build_basic_alg()
    trainingDataStr = build_equal_training_data(10)
    modelStr = build_nn()
   
    return make_sim_json(nameStr, generationStr, algStr, trainingDataStr, modelStr)

def run_sim(sim_filename="blank_sim.json"):
    os.chdir('..')
    print(os.getcwd())
    os.system("bin\GeneticSim " + os.getcwd()+'/tools/'+sim_filename)
 
if __name__ == '__main__':   
    run_sweep_with_graphs("test", "mutSize", [0.01, 0.02, 0.03], Algorithm())