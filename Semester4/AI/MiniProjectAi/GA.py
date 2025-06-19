import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import random
from scipy import stats
import pandas as pd
import seaborn as sns
from typing import List, Tuple, Dict
import warnings

warnings.filterwarnings('ignore')


# =============================================================================
# TASK 1: Function Selection and Definition
# =============================================================================

def cross_in_tray(x, y):
    """
    Cross-in-Tray function
    Domain: [-10, 10] × [-10, 10]
    Global minimum: f(±1.3491, ±1.3491) = -2.06261
    """
    term = np.abs(100 - np.sqrt(x ** 2 + y ** 2) / np.pi)
    return -0.0001 * (np.abs(np.sin(x) * np.sin(y) * np.exp(term)) + 1) ** 0.1


def eggholder(x, y):
    """
    Eggholder function
    Domain: [-512, 512] × [-512, 512]
    Global minimum: f(512, 404.2319) = -959.6407
    """
    return -(y + 47) * np.sin(np.sqrt(np.abs(x / 2 + y + 47))) - x * np.sin(np.sqrt(np.abs(x - (y + 47))))


# Function domains
FUNCTIONS = {
    'cross_in_tray': {
        'func': cross_in_tray,
        'domain': [(-10, 10), (-10, 10)],
        'global_min': -2.06261
    },
    'eggholder': {
        'func': eggholder,
        'domain': [(-512, 512), (-512, 512)],
        'global_min': -959.6407
    }
}


# =============================================================================
# TASK 2: Function Implementation and Visualization
# =============================================================================

def visualize_functions():
    """Create contour and surface plots for both functions"""
    fig, axes = plt.subplots(2, 2, figsize=(15, 12))

    # Cross-in-Tray function
    x1 = np.linspace(-10, 10, 200)
    y1 = np.linspace(-10, 10, 200)
    X1, Y1 = np.meshgrid(x1, y1)
    Z1 = cross_in_tray(X1, Y1)

    # Contour plot
    cont1 = axes[0, 0].contourf(X1, Y1, Z1, levels=50, cmap='viridis')
    axes[0, 0].set_title('Cross-in-Tray Function - Contour')
    axes[0, 0].set_xlabel('x')
    axes[0, 0].set_ylabel('y')
    plt.colorbar(cont1, ax=axes[0, 0])

    # Surface plot (simplified for subplot)
    axes[0, 1].contour(X1, Y1, Z1, levels=20, cmap='viridis')
    axes[0, 1].set_title('Cross-in-Tray Function - Contour Lines')
    axes[0, 1].set_xlabel('x')
    axes[0, 1].set_ylabel('y')

    # Eggholder function
    x2 = np.linspace(-512, 512, 200)
    y2 = np.linspace(-512, 512, 200)
    X2, Y2 = np.meshgrid(x2, y2)
    Z2 = eggholder(X2, Y2)

    # Contour plot
    cont2 = axes[1, 0].contourf(X2, Y2, Z2, levels=50, cmap='plasma')
    axes[1, 0].set_title('Eggholder Function - Contour')
    axes[1, 0].set_xlabel('x')
    axes[1, 0].set_ylabel('y')
    plt.colorbar(cont2, ax=axes[1, 0])

    # Surface plot (simplified for subplot)
    axes[1, 1].contour(X2, Y2, Z2, levels=20, cmap='plasma')
    axes[1, 1].set_title('Eggholder Function - Contour Lines')
    axes[1, 1].set_xlabel('x')
    axes[1, 1].set_ylabel('y')

    plt.tight_layout()
    plt.show()


# =============================================================================
# TASK 3: Genetic Algorithm Implementation
# =============================================================================

class GeneticAlgorithm:
    def __init__(self, func_name, representation='real', crossover='arithmetic',
                 population_size=50, generations=100, mutation_rate=0.1,
                 crossover_rate=0.8, alpha=0.5):
        self.func_info = FUNCTIONS[func_name]
        self.func = self.func_info['func']
        self.domain = self.func_info['domain']
        self.representation = representation
        self.crossover_type = crossover
        self.population_size = population_size
        self.generations = generations
        self.mutation_rate = mutation_rate
        self.crossover_rate = crossover_rate
        self.alpha = alpha  # For BLX-α crossover
        self.fitness_evaluations = 0
        self.max_evaluations = population_size * generations

        # Binary encoding parameters
        self.bits_per_var = 16 if representation == 'binary' else None

    def initialize_population(self):
        """Initialize population based on representation"""
        if self.representation == 'binary':
            return self._initialize_binary_population()
        else:
            return self._initialize_real_population()

    def _initialize_binary_population(self):
        """Initialize binary encoded population"""
        population = []
        for _ in range(self.population_size):
            individual = []
            for i in range(2):  # 2D functions
                # Generate random binary string
                binary_str = ''.join([str(random.randint(0, 1)) for _ in range(self.bits_per_var)])
                individual.append(binary_str)
            population.append(individual)
        return population

    def _initialize_real_population(self):
        """Initialize real-valued population"""
        population = []
        for _ in range(self.population_size):
            individual = []
            for i in range(2):  # 2D functions
                low, high = self.domain[i]
                individual.append(random.uniform(low, high))
            population.append(individual)
        return population

    def decode_individual(self, individual):
        """Decode individual to real values"""
        if self.representation == 'binary':
            decoded = []
            for i, binary_str in enumerate(individual):
                # Convert binary to decimal
                decimal = int(binary_str, 2)
                # Scale to domain
                low, high = self.domain[i]
                max_val = 2 ** self.bits_per_var - 1
                real_val = low + (high - low) * decimal / max_val
                decoded.append(real_val)
            return decoded
        else:
            return individual.copy()

    def evaluate_fitness(self, individual):
        """Evaluate fitness of an individual"""
        self.fitness_evaluations += 1
        decoded = self.decode_individual(individual)
        return self.func(decoded[0], decoded[1])

    def tournament_selection(self, population, fitnesses, tournament_size=3):
        """Tournament selection"""
        selected = []
        for _ in range(self.population_size):
            # Random tournament
            tournament_indices = random.sample(range(len(population)), tournament_size)
            tournament_fitnesses = [fitnesses[i] for i in tournament_indices]
            winner_idx = tournament_indices[np.argmin(tournament_fitnesses)]
            selected.append(population[winner_idx].copy())
        return selected

    def crossover(self, parent1, parent2):
        """Perform crossover based on representation and type"""
        if random.random() > self.crossover_rate:
            return parent1.copy(), parent2.copy()

        if self.representation == 'binary':
            if self.crossover_type == '1-point':
                return self._one_point_crossover(parent1, parent2)
            else:  # 2-point
                return self._two_point_crossover(parent1, parent2)
        else:
            if self.crossover_type == 'arithmetic':
                return self._arithmetic_crossover(parent1, parent2)
            else:  # BLX-α
                return self._blx_alpha_crossover(parent1, parent2)

    def _one_point_crossover(self, parent1, parent2):
        """One-point crossover for binary representation"""
        offspring1, offspring2 = [], []
        for i in range(2):  # For each variable
            point = random.randint(1, self.bits_per_var - 1)
            child1 = parent1[i][:point] + parent2[i][point:]
            child2 = parent2[i][:point] + parent1[i][point:]
            offspring1.append(child1)
            offspring2.append(child2)
        return offspring1, offspring2

    def _two_point_crossover(self, parent1, parent2):
        """Two-point crossover for binary representation, imparte
        stringul in 3 parti si ia jumatatea de la prima parte si o pune
        la o doua parte si invers"""
        offspring1, offspring2 = [], []
        for i in range(2):  # For each variable
            point1 = random.randint(1, self.bits_per_var - 2)
            point2 = random.randint(point1 + 1, self.bits_per_var - 1)

            child1 = parent1[i][:point1] + parent2[i][point1:point2] + parent1[i][point2:]
            child2 = parent2[i][:point1] + parent1[i][point1:point2] + parent2[i][point2:]
            offspring1.append(child1)
            offspring2.append(child2)
        return offspring1, offspring2

    def _arithmetic_crossover(self, parent1, parent2):
        """Arithmetic crossover for real-valued representation"""
        alpha = random.random()
        offspring1 = [alpha * parent1[i] + (1 - alpha) * parent2[i] for i in range(2)]
        offspring2 = [(1 - alpha) * parent1[i] + alpha * parent2[i] for i in range(2)]
        return offspring1, offspring2

    def _blx_alpha_crossover(self, parent1, parent2):
        """BLX-α crossover for real-valued representation"""
        offspring1, offspring2 = [], []
        for i in range(2):
            min_val = min(parent1[i], parent2[i])
            max_val = max(parent1[i], parent2[i])
            range_val = max_val - min_val

            # Extend range by alpha
            low = min_val - self.alpha * range_val
            high = max_val + self.alpha * range_val

            # Constrain to domain
            domain_low, domain_high = self.domain[i]
            low = max(low, domain_low)
            high = min(high, domain_high)

            offspring1.append(random.uniform(low, high))
            offspring2.append(random.uniform(low, high))

        return offspring1, offspring2

    def mutate(self, individual):
        """Perform mutation based on representation"""
        if self.representation == 'binary':
            return self._binary_mutation(individual)
        else:
            return self._real_mutation(individual)

    def _binary_mutation(self, individual):
        """Binary mutation (bit flip)"""
        mutated = []
        for gene in individual:
            mutated_gene = ""
            for bit in gene:
                if random.random() < self.mutation_rate:
                    mutated_gene += '1' if bit == '0' else '0'
                else:
                    mutated_gene += bit
            mutated.append(mutated_gene)
        return mutated

    def _real_mutation(self, individual):
        """Real-valued mutation (Gaussian)"""
        mutated = []
        for i, gene in enumerate(individual):
            if random.random() < self.mutation_rate:
                low, high = self.domain[i]
                sigma = (high - low) * 0.1  # 10% of range
                new_gene = gene + random.gauss(0, sigma)
                # Constrain to domain
                new_gene = max(min(new_gene, high), low)
                mutated.append(new_gene)
            else:
                mutated.append(gene)
        return mutated

    def run(self):
        """Run the genetic algorithm"""
        population = self.initialize_population()
        best_fitness_history = []
        mean_fitness_history = []

        for generation in range(self.generations):
            # Evaluate fitness
            fitnesses = [self.evaluate_fitness(ind) for ind in population]

            # Track statistics
            best_fitness = min(fitnesses)
            mean_fitness = np.mean(fitnesses)
            best_fitness_history.append(best_fitness)
            mean_fitness_history.append(mean_fitness)

            # Selection
            selected = self.tournament_selection(population, fitnesses)

            # Crossover and mutation
            new_population = []
            for i in range(0, len(selected), 2):
                parent1 = selected[i]
                parent2 = selected[i + 1] if i + 1 < len(selected) else selected[0]

                child1, child2 = self.crossover(parent1, parent2)
                child1 = self.mutate(child1)
                child2 = self.mutate(child2)

                new_population.extend([child1, child2])

            population = new_population[:self.population_size]

        # Final evaluation
        final_fitnesses = [self.evaluate_fitness(ind) for ind in population]
        best_idx = np.argmin(final_fitnesses)
        best_individual = population[best_idx]
        best_fitness = final_fitnesses[best_idx]

        return {
            'best_fitness': best_fitness,
            'best_individual': self.decode_individual(best_individual),
            'fitness_history': best_fitness_history,
            'mean_history': mean_fitness_history,
            'evaluations': self.fitness_evaluations
        }


# =============================================================================
# TASK 4: Optimization Experiments
# =============================================================================

def run_experiments():
    """Run all experimental configurations"""
    functions = ['cross_in_tray', 'eggholder']
    representations = ['binary', 'real']
    crossover_types = {
        'binary': ['1-point', '2-point'],
        'real': ['arithmetic', 'blx-alpha']
    }

    results = {}
    runs_per_config = 30

    total_configs = sum(len(crossover_types[rep]) for rep in representations) * len(functions)
    config_count = 0

    for func_name in functions:
        results[func_name] = {}

        for representation in representations:
            for crossover in crossover_types[representation]:
                config_count += 1
                config_name = f"{representation}_{crossover}"
                print(f"Running configuration {config_count}/{total_configs}: {func_name} - {config_name}")

                run_results = []
                for run in range(runs_per_config):
                    if run % 10 == 0:
                        print(f"  Run {run + 1}/{runs_per_config}")

                    ga = GeneticAlgorithm(
                        func_name=func_name,
                        representation=representation,
                        crossover=crossover,
                        population_size=50,
                        generations=100,
                        mutation_rate=0.1,
                        crossover_rate=0.8
                    )

                    result = ga.run()
                    run_results.append(result['best_fitness'])

                results[func_name][config_name] = run_results

    return results


# =============================================================================
# TASK 5: Statistical Analysis
# =============================================================================

def statistical_analysis(results):
    """Perform statistical analysis of results"""
    analysis_results = {}

    for func_name, func_results in results.items():
        print(f"\n{'=' * 60}")
        print(f"STATISTICAL ANALYSIS FOR {func_name.upper()} FUNCTION")
        print(f"{'=' * 60}")

        # Prepare data for analysis
        config_names = list(func_results.keys())
        data = []

        # Calculate descriptive statistics
        stats_table = []
        for config in config_names:
            values = func_results[config]
            stats_table.append({
                'Configuration': config,
                'Mean': np.mean(values),
                'Std': np.std(values),
                'Min': np.min(values),
                'Max': np.max(values),
                'Median': np.median(values)
            })
            data.extend([(config, val) for val in values])

        stats_df = pd.DataFrame(stats_table)
        print("\nDescriptive Statistics:")
        print(stats_df.to_string(index=False, float_format='%.6f'))

        # Perform ANOVA
        groups = [func_results[config] for config in config_names]
        f_stat, p_value_anova = stats.f_oneway(*groups)

        print(f"\nANOVA Results:")
        print(f"F-statistic: {f_stat:.6f}")
        print(f"p-value: {p_value_anova:.6f}")
        print(f"Significant difference: {'Yes' if p_value_anova < 0.05 else 'No'}")

        # Pairwise t-tests
        print(f"\nPairwise t-tests (with Bonferroni correction):")
        n_comparisons = len(config_names) * (len(config_names) - 1) // 2
        alpha_corrected = 0.05 / n_comparisons

        pairwise_results = []
        for i in range(len(config_names)):
            for j in range(i + 1, len(config_names)):
                config1, config2 = config_names[i], config_names[j]
                t_stat, p_val = stats.ttest_ind(func_results[config1], func_results[config2])
                significant = p_val < alpha_corrected
                pairwise_results.append({
                    'Config 1': config1,
                    'Config 2': config2,
                    't-statistic': t_stat,
                    'p-value': p_val,
                    'Significant': 'Yes' if significant else 'No'
                })

        pairwise_df = pd.DataFrame(pairwise_results)
        print(pairwise_df.to_string(index=False, float_format='%.6f'))

        analysis_results[func_name] = {
            'descriptive_stats': stats_df,
            'anova': {'f_stat': f_stat, 'p_value': p_value_anova},
            'pairwise_tests': pairwise_df
        }

    return analysis_results


def plot_results(results):
    """Create visualization of results"""
    fig, axes = plt.subplots(2, 2, figsize=(15, 10))

    for i, (func_name, func_results) in enumerate(results.items()):
        # Box plot
        data_for_boxplot = []
        labels = []
        for config, values in func_results.items():
            data_for_boxplot.append(values)
            labels.append(config.replace('_', '\n'))

        axes[i, 0].boxplot(data_for_boxplot, labels=labels)
        axes[i, 0].set_title(f'{func_name.replace("_", " ").title()} - Box Plot')
        axes[i, 0].set_ylabel('Fitness Value')
        axes[i, 0].tick_params(axis='x', rotation=45)

        # Bar plot of means
        means = [np.mean(values) for values in data_for_boxplot]
        stds = [np.std(values) for values in data_for_boxplot]

        axes[i, 1].bar(labels, means, yerr=stds, capsize=5, alpha=0.7)
        axes[i, 1].set_title(f'{func_name.replace("_", " ").title()} - Mean ± Std')
        axes[i, 1].set_ylabel('Mean Fitness Value')
        axes[i, 1].tick_params(axis='x', rotation=45)

    plt.tight_layout()
    plt.show()


# =============================================================================
# MAIN EXECUTION
# =============================================================================

def main():
    print("GENETIC ALGORITHM BENCHMARK OPTIMIZATION")
    print("=" * 50)

    # Task 1: Function definitions already completed above
    print("\nTask 1: Function Selection")
    print("f1: Cross-in-Tray function, Domain: [-10, 10] × [-10, 10]")
    print("f2: Eggholder function, Domain: [-512, 512] × [-512, 512]")

    # Task 2: Visualization
    print("\nTask 2: Function Visualization")
    visualize_functions()

    # Task 3: GA implementation already completed above
    print("\nTask 3: Genetic Algorithm Implementation - Complete")

    # Task 4: Run full experiments
    print("\nTask 4: Running Full Optimization Experiments...")
    print("Running 30 independent runs for each of 8 configurations (240 total runs)")

    # Full experiment with all configurations
    functions = ['cross_in_tray', 'eggholder']
    representations = ['binary', 'real']
    crossover_types = {
        'binary': ['1-point', '2-point'],
        'real': ['arithmetic', 'blx-alpha']
    }

    results = {}
    runs_per_config = 30

    total_configs = sum(len(crossover_types[rep]) for rep in representations) * len(functions)
    config_count = 0

    for func_name in functions:
        results[func_name] = {}
        print(f"\n--- Processing {func_name.upper()} function ---")

        for representation in representations:
            for crossover in crossover_types[representation]:
                config_count += 1
                config_name = f"{representation}_{crossover}"
                print(f"Configuration {config_count}/{total_configs}: {config_name}")

                run_results = []
                for run in range(runs_per_config):
                    if (run + 1) % 5 == 0:
                        print(f"  Completed {run + 1}/{runs_per_config} runs")

                    ga = GeneticAlgorithm(
                        func_name=func_name,
                        representation=representation,
                        crossover=crossover,
                        population_size=50,  # Full population size
                        generations=100,  # Full generations
                        mutation_rate=0.1,
                        crossover_rate=0.8,
                        alpha=0.5  # For BLX-α crossover
                    )

                    result = ga.run()
                    run_results.append(result['best_fitness'])

                results[func_name][config_name] = run_results
                mean_fitness = np.mean(run_results)
                std_fitness = np.std(run_results)
                best_fitness = min(run_results)
                print(f"  Results: Mean={mean_fitness:.6f}, Std={std_fitness:.6f}, Best={best_fitness:.6f}")

    # Task 5: Statistical analysis
    print("\nTask 5: Statistical Analysis")
    analysis_results = statistical_analysis(results)

    # Plot results
    print("\nGenerating plots...")
    plot_results(results)

    # Save results to file
    print("\nSaving results to CSV files...")
    for func_name, func_results in results.items():
        df_data = []
        for config, values in func_results.items():
            for run_idx, value in enumerate(values):
                df_data.append({
                    'Function': func_name,
                    'Configuration': config,
                    'Run': run_idx + 1,
                    'Fitness': value
                })

        df = pd.DataFrame(df_data)
        filename = f"{func_name}_results.csv"
        df.to_csv(filename, index=False)
        print(f"Saved {filename}")

    print("\n" + "=" * 50)
    print("FULL ANALYSIS COMPLETE")
    print("=" * 50)
    print(f"Total configurations tested: {total_configs}")
    print(f"Total runs completed: {total_configs * runs_per_config}")
    print("Results saved to CSV files for further analysis.")


if __name__ == "__main__":
    main()