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
    pcomb = make_null_abstract("RandomCrossingCombiner")
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
    
def build_nn_template(layerSizes):
    layerStr = '[' + ','.join([str(x) for x in layerSizes]) + ']'
    totalWeights = sum([layerSizes[i]*layerSizes[i-1] for i in range(len(layerSizes)-1)])
    weightStr = '[' + ','.join(['0.0']*totalWeights) + ']'
    nnStr = '{ typename : "NeuralModel", data : {layer_sizes : '+layerStr+', weights : '+weightStr+'}}'
    return nnStr
   
def build_nn():
    return build_nn_template([28*28, 10])
    
def build_nn_3layer():
    return build_nn_template([28*28, 10, 10])
    
def build_big_nn():
    return build_nn_template([28*28, 50, 20, 10])

def build_downsampling_template(pool_width, pool_height, image_width, image_height):
    dsStr = '{ typename : "DownSamplingModel", data : { pool_width : '+str(pool_width)+', pool_height : '+str(pool_height)+', image_width : '+str(image_width)+', image_height : '+str(image_height)+'}}'
    return dsStr
   
def build_conv_template(kernel_width, kernel_height, image_width, image_height):
    convStr = '{ typename: "ConvolutionModel", data : { kernel_width : '+str(kernel_width)+', kernel_height : '+str(kernel_height)+', image_width : '+str(image_width)+', image_height : '+str(image_height)+', weights : '+'[' + ','.join(['0.0']*(kernel_width*kernel_height))+']'+'}}'
    return convStr
   
# CNN
# Conv -> Downsampling -> NN
# 5 Feature maps -> 3x3 Max Pooling -> Fully connected
def build_cnn():
    convStr = build_conv_template(3, 3, 28, 28)
    downSamplingStr = build_downsampling_template(3, 3, 26, 26)
    nnStr = build_nn_template([9*9, 10, 10])
    return '{ typename : "InterconnectedGeneticModel", data : { layers : [['+'],['.join([convStr, downSamplingStr, nnStr])+']]}}'
    
# Simulation JSON
    
def make_sim_json(name="\"blank_sim\"", generations="1", alg="null", trainingData="null", model="null"):
    return '{' + "name : {0}, generations : {1}, algorithm : {2}, model_template : {3}, training_data : {4}".format(name, generations, alg, model, trainingData) + '}'
    
def generate_run_file(run_name, alg, generations=10, num_images=10):
    sim_json = make_sim_json('"'+run_name+'"', str(generations), alg.to_json(), build_equal_training_data(num_images), build_big_nn())
    json_file = open(run_name+'.json', 'w+')
    json_file.write(sim_json)
    json_file.close()
    return run_name+'.json'
    
def generate_sweep_files(sweep_name, var_name, sweep_vals, alg, generations=10, num_images=10):
    filenames = []
    for val in sweep_vals:
        setattr(alg, var_name, val)
        sim_name = sweep_name + '_' + str(val)
        filenames.append(generate_run_file(sim_name, alg, generations, num_images))
    return filenames
  
def run_alg(filename):
    os.system(os.path.join('..', 'bin', 'GeneticSim') + ' ' + filename)
    file = open('.'.join(filename.split(".")[:-1])+'.csv', 'r')
    run_data = [line.rstrip() for line in file if line != '\n']
    avg_data = [float(x.split(',')[0]) for x in run_data]
    best_data = [float(x.split(',')[1]) for x in run_data]
    file.close()
    return best_data[-1]
    
def meta_optimize(meta_name, var_name, alg, generations=10, num_images=10, max_depth=3):
    iterations = 1
    current_depth = 1
    current_best = run_alg(generate_run_file(meta_name+'_0', alg, generations, num_images))
    going_up = 1
    
    while current_depth <= max_depth:
        print("Current best is " + str(current_best))
        setattr(alg, var_name, getattr(alg, var_name) + going_up*(10**-current_depth))
        print("Set " + var_name + " to " + str(getattr(alg, var_name)))
        new_best = run_alg(generate_run_file(meta_name+'_'+str(iterations), alg, generations, num_images))
        print("New best is " + str(new_best))
        if (new_best < current_best):
            current_depth += 1
            going_up = going_up * -1
        current_best = new_best
        iterations += 1
  
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
    
    parser.add_argument('-g', '--gen-size', type=int, default=500)
    parser.add_argument('-o', '--offset', type=float, default=0.1)
    parser.add_argument('-c', '--mut-chance', type=float, default=1)
    parser.add_argument('-s', '--mut-size', type=float, default=0.1)
    parser.add_argument('-e', '--elitism', type=float, default=0.1)
    
    return parser.parse_args()
 
if __name__ == '__main__':
    args = get_args()
   
    sweep_vals = []
    v = args.sweep_start
    while v <= args.sweep_stop:
        sweep_vals.append(v)
        v += args.sweep_step
        
    run_sweep(args.sim_name, args.sweep_var, sweep_vals, Algorithm(args), args.generations, args.num_images)
    
    #meta_optimize("test", args.sweep_var, Algorithm(args), args.generations, args.num_images)