import argparse
import os
import sys


parser = argparse.ArgumentParser()
parser.add_argument(
    '--nh_dir',
    type=str,
    default=None,
    required=True,
    help='Location of the New Horizons mod'
)

parser.add_argument(
    '--output_dir',
    type=str,
    default=None,
    required=True,
    help='Folder for converted output'
)

class ship_model:
    """
    Model class to store a dictionary with all the necessary parameters as well
        as flags to indicate gender and processing status
    """

    def __init__(self, model_list,
                nh_dir=None,
                output_dir=None):
        """
        Initialization function of the storm_model class

        Parameters
        ----------
        model_list: list
            list with all entries read from initModel.c
        nh_dir: str
            Location of the New Horizons mod
        output_dir: str
            Folder for converted output                   
        """

        self.nh_dir = nh_dir
        self.output_dir = output_dir

        # create list with animation as comment
        self.comments_and_ending = ['//'+line for line in model_list if '.ani' in line and '//' not in line]
        #add all comments and ending
        self.comments_and_ending += [line for line in model_list if 'model.' not in line or '//' in line.split('model.')[0] or 'AssignModel' in line or 'IF' in line]

        self.only_parameters = [line for line in model_list if 'model.' in line and '//' not in line.split('model.')[0] and 'AssignModel' not in line and '.ani' not in line]
        self.model_parameters = {}

        # Fill parameter dictionary
        for line in self.only_parameters:
            parameter = line.split('model.')[1].split('=')[0].replace(' ', '').replace('\t', '')
            self.model_parameters[parameter] = line.split('=')[1].replace('\t', '').strip()
        
        # Make sure the model has an assigned sex
        if 'sex' not in self.model_parameters:
            self.model_parameters['sex'] = '"man";'

        # Store flag to indicate that the model has an animation different than "man" or "woman_sit"
        self.standard_ani = True
        if 'ani' in self.model_parameters:
            if self.model_parameters['ani'] == '"woman_sit";' or self.model_parameters['ani'] == '"man";':
                self.standard_ani = True
            else:
                self.standard_ani = False

        # Assemble model file name
        self.model = self.model_parameters['id'].split('"')[1]
        self.model_file = self.model + ".gm"

        # clean sex string, set animation files, and conversion flags
        self.convert_potc_to_coas_man=False
        self.convert_potc_to_coas_woman=False
        if 'woman' in self.model_parameters['sex']:
            self.sex = 'woman'
            self.an_path = self.output_dir + f'/RESOURCE/animation/woman_coas.an'
            self.convert_potc_to_coas_woman = True
            self.model_parameters['ani'] = '"woman_coas";'
            
        elif 'monkey' in self.model_parameters['sex']:
            self.sex = 'monkey'

        elif 'skeleton' in self.model_parameters['sex']:
            self.sex = 'skeleton'
            self.an_path = self.output_dir + f'/RESOURCE/animation/man_coas.an'
            self.convert_potc_to_coas_man = True
            self.model_parameters['ani'] = f'"man";'
        else:
            self.sex = 'man'
            self.an_path = self.output_dir + f'/RESOURCE/animation/man_coas.an'
            self.convert_potc_to_coas_man = True

        # Define parameters for import
        self.filepath = self.nh_dir + f'/RESOURCE/MODELS/Characters/{self.model_file}'
        self.textures_path = self.nh_dir + '/RESOURCE/Textures/Characters/'
        
        self.fix_coas_man_head = False
        self.convert_coas_to_potc_man = False
        self.convert_coas_to_potc_woman = False

        # Define parameters for export
        self.filepath_out = self.output_dir + f'/RESOURCE/MODELS/Characters/{self.model_file}'


    def print_to_file(self, initShipsOutputFile):
        """
        Function to print model into file

        Parameters
        ----------
        initShipsOutputFile: file
            file where to print the lines of each model       
        """

        for key, value in self.model_parameters.items():
            initShipsOutputFile.write(f'\tmodel.{key} = {value}\n')

        for line in self.comments_and_ending:
            initShipsOutputFile.write(line)


def ships_add_wake(
    nh_dir=None,
    output_dir=None
    ):
    """Batch process initModels.c

    Parameters
    ----------
    nh_dir: str
        Location of the New Horizons mod
    output_dir: str
        Folder for converted output
    """

    initShipsFile = nh_dir + '/PROGRAM/Ships/Ships_init.c'
    initShipsFile = open(initShipsFile, 'r')
    initModelslines = initShipsFile.readlines()

    initShipsOutputFile = output_dir + 'Ships_init.c'
    initShipsOutputFile = open(initShipsOutputFile, 'w')

    new_model_definition = False
    ship_has_wake = False
    for index, line in enumerate(initModelslines):

        initShipsOutputFile.write(line)

        # Find beginning of ship model definition
        if new_model_definition:
            
            if not ship_has_wake:
                

        if 'AddCharacterModel(model);' in line and not model_definition_start:
            model_definition_start = True

        


        if not model_definition_start:
            initShipsOutputFile.write(line)

            if 'MODEL_HIGH = 0;' in line:
                model_definition_start = True
                model_found = False
                block_comment_found = False
        
        else:

            # Find where the model begings and trigger flag
            if not model_found:

                # Begin list of lines associated with a model
                if 'model.description' in line:
                    model_found = True
                    model_list = [line]
                else:
                    initShipsOutputFile.write(line)

            # Append lines unitl the last line of the model is found
            else:
                model_list += [line]

                # Close the model, trigger conversion, and print to file
                if 'AddCharacterModel(model);' in line:
                    model_found = False
                    model = storm_model(model_list, nh_dir, output_dir)
                    if model.sex is not 'monkey' and os.path.exists(model.filepath):
                        bpy.ops.object.select_all(action='SELECT')
                        bpy.ops.object.delete()

                        # Import
                        print(model.filepath, model.textures_path, model.an_path, '\nhead', model.fix_coas_man_head, '\nmc2p', model.convert_coas_to_potc_man, '\nmp2c', model.convert_potc_to_coas_man, '\nwc2p', model.convert_coas_to_potc_woman, '\nwp2c', model.convert_potc_to_coas_woman)
                        bpy.ops.storm.import_gm(filepath_in=model.filepath, 
                                                textures_path=model.textures_path,
                                                an_path=model.an_path,
                                                fix_coas_man_head=model.fix_coas_man_head,
                                                convert_coas_to_potc_man=model.convert_coas_to_potc_man,
                                                convert_potc_to_coas_man=model.convert_potc_to_coas_man,
                                                convert_coas_to_potc_woman=model.convert_coas_to_potc_woman,
                                                convert_potc_to_coas_woman=model.convert_potc_to_coas_woman)

                        # Select
                        objectToSelect = bpy.data.objects["root"]
                        objectToSelect.select_set(True)    
                        bpy.context.view_layer.objects.active = objectToSelect

                        # Export
                        bpy.ops.storm.export_gm(filepath_out=model.filepath_out)

                        # Clear collection
                        collection = bpy.data.collections.get(model.model)
                        for obj in collection.objects:
                            bpy.data.objects.remove(obj, do_unlink=True)
                        bpy.data.collections.remove(collection)

                        # Open new file
                        bpy.ops.wm.read_homefile()

                    model.print_to_file(initShipsOutputFile)


    initShipsFile.close()
    initShipsOutputFile.close()


if __name__ == "__main__":

    print(sys.argv[sys.argv.index("--")+1:])

    print(parser.parse_known_args(sys.argv[sys.argv.index("--")+1:]))
    args = vars(parser.parse_known_args(sys.argv[sys.argv.index("--")+1:])[0])
    print(args)

    ships_add_wake(**args)