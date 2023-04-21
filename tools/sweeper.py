import os
import random
import argparse

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
   
def select_images_from_dir(path, num_images=1):
    all_images = os.listdir(path)
    return random.sample(all_images, num_images)
    
def build_equal_training_data(num_images=1):
    t_data = []
    for i in range(10):
        abs_path = os.path.join('..', 'data', 'digit_training', str(i))
        image_list = select_images_from_dir(abs_path, num_images)
        t_data = t_data + [make_image_tdata('"'+os.path.join(abs_path,x)+'"', i) for x in image_list]
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
    def __init__(self, args):
        self.generationSize = args.gen_size
        self.offset = args.offset
        self.mutChance = args.mut_chance
        self.mutSize = args.mut_size
        self.elitism = args.elitism
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
    
def build_nn_3layer():
    layerStr = "[" + str(28*28) + ',' + str(10) + ',' + str(10) + ']'
    weightStr = "[" + ','.join(["0.0" for x in range(28*28*10 + 10*10)]) + ']'
    dataStr = "{" + "layer_sizes: {0}, weights: {1}".format(layerStr, weightStr) + "}"
    typeStr = "\"NeuralModel\""
    nnStr = "{" + "typename : {0}, data : {1}".format(typeStr, dataStr) + "}"
    return nnStr
    
# Simulation JSON
    
def make_sim_json(name="\"blank_sim\"", generations="1", alg="null", trainingData="null", model="null"):
    return '{' + "name : {0}, generations : {1}, algorithm : {2}, model_template : {3}, training_data : {4}".format(name, generations, alg, model, trainingData) + '}'
    
def generate_sweep_files(sweep_name, var_name, sweep_vals, alg, generations=10, num_images=10):
    filenames = []
    for val in sweep_vals:
        setattr(alg, var_name, val)
        sim_name = sweep_name + '_' + str(val)
        sim_json = make_sim_json('"'+sim_name+'"', str(generations), alg.to_json(), build_equal_training_data(num_images), build_nn_3layer())
        json_file = open(sim_name+'.json', 'w+')
        filenames.append(sim_name+'.json')
        json_file.write(sim_json)
        json_file.close()
    return filenames
        
def run_sweep(sweep_name, var_name, sweep_vals, alg, generations=10, num_images=10):
    files = generate_sweep_files(sweep_name, var_name, sweep_vals, alg, generations, num_images)
    for f in files:
        os.system(os.path.join('..', 'bin', 'GeneticSim') + ' ' + f)
    return ['.'.join(x.split('.')[:-1]) + '.csv' for x in files]
    
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
 
def get_args():
    parser = argparse.ArgumentParser()
    
    parser.add_argument('sim_name')
    parser.add_argument('sweep_var', choices=['mutChance','mutSize','generationSize','offset','elitism'])
    parser.add_argument('sweep_start', type=float)
    parser.add_argument('sweep_stop', type=float)
    parser.add_argument('sweep_step', type=float)
    parser.add_argument('generations', type=int)
    parser.add_argument('num_images', type=int)
    
    parser.add_argument('-g', '--gen-size', type=int, default=100)
    parser.add_argument('-o', '--offset', type=float, default=1.0)
    parser.add_argument('-c', '--mut-chance', type=float, default=0.05)
    parser.add_argument('-s', '--mut-size', type=float, default=0.01)
    parser.add_argument('-e', '--elitism', type=float, default=0.05)
    
    return parser.parse_args()
 
if __name__ == '__main__':
    args = get_args()
   
    sweep_vals = []
    v = args.sweep_start
    while v <= args.sweep_stop:
        sweep_vals.append(v)
        v += args.sweep_step
        
    run_sweep(args.sim_name, args.sweep_var, sweep_vals, Algorithm(args), args.generations, args.num_images)