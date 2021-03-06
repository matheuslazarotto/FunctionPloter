# Auxiliary plot routines
#
# Made by: Matheus J. Lazarotto (30/09/2020 -- 28/12/2020)

# Import auxiliary file
import sys
sys.path.append('../python')
from aux_par import *

from matplotlib import cm
import matplotlib.pyplot as plt
from matplotlib.ticker import FuncFormatter
from matplotlib.ticker import MultipleLocator
from matplotlib.ticker import FormatStrFormatter

# Plot routine 
def plot_functions(dic_dat, setup_dat):
    # Edit text font
    font = {'family' : 'serif',
            'weight' : 'normal',
            'size'   : 55}
    plt.rc('font', **font)
    
    # plt.rc('text', usetex = True)  # LaTeX text
    # plt.rc('font', family = 'serif', size = 80)
    fig, ax = plt.subplots(figsize = (30, 25))

    # Get data
    funct_number = setup_dat['nFunctions']
    Xmin = setup_dat['x_min']
    Xmax = setup_dat['x_max']
    Ymin = setup_dat['y_min']
    Ymax = setup_dat['y_max']

    # Set X axes #
    ax.set_xlim([Xmin, Xmax])
    ax.set_xlabel("x", rotation = 0, labelpad = 15, fontsize = 70)

    # Set Y axes #
    ax.set_ylim([Ymin, Ymax])
    ax.set_ylabel("f(x)", rotation = 0, labelpad = 25, fontsize = 70)

    # Set global features #
    ax.tick_params(which = 'major', direction = 'in', length = 18, 
                   width = 2.2, bottom = True, top = True, left = True, 
                   right = True, pad = 20)
    ax.tick_params(which = 'minor', direction = 'in', length = 10, 
                   width = 1.8, bottom = True, top = True, left = True, 
                   right = True)
    for axis in ['top','bottom','left','right']:
        ax.spines[axis].set_linewidth(4.0)

    # Loop over data dictionary
    for i in range(funct_number):
        color = colors_std_matplotlib[i]
        plt.plot(dic_dat['x'][i], dic_dat['y'][i], 
                 linestyle = '-', linewidth = 4, color = color, 
                 label = 'f(x) := %s' % dic_dat['expressions'][i])

    # Constants and Legend
    text_string = []
    for key in setup_dat['constants']:
        string = key + ' = %.5f' % setup_dat['constants'][key] 
        text_string.append(string)
    
    text_tuple = tuple(text_string)
    text_tuple = '\n'.join(text_tuple)

    props = dict(boxstyle = 'round', facecolor = 'lightsteelblue', alpha = 0.5)
    ax.text(0.02, 0.98, text_tuple, transform=ax.transAxes, fontsize=34,
            verticalalignment = 'top', bbox = props)

    plt.grid()
    plt.legend(loc = 'best', ncol = 1, prop = {'size': 38})

    # Save and close #
    fig.patch.set_facecolor('white')
    fig.patch.set_alpha(1.0)
    ax.patch.set_facecolor('white')
    ax.patch.set_alpha(1.0)
    plt.savefig('functions.png', bbox_inches='tight', 
                 facecolor=fig.get_facecolor(), edgecolor='none')
    plt.clf()
    plt.close()
