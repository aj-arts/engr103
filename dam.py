import csv

def read_csv(filename):
    with open(filename, 'r') as f:
        reader = csv.reader(f)
        data = list(reader)
    return data

#print(read_csv('energy_use_terrawatthours.csv'))

data = read_csv('energy_use_terrawatthours.csv')

#the total power consumption of the world in a given year given power type
def total_power_consumption(data, year, power_type):
    total = 0
    for row in data:
        if (row[1] == str(year) and row[2] == power_type):
            total += float(row[3])
    return total

def total_power_consumption_year(data, year):
    return total_power_consumption(data, year, 'Clean') + total_power_consumption(data, year, 'Fossil')

total_increase_2000_2021 = total_power_consumption_year(data, 2021) - total_power_consumption_year(data, 2000)
print('The total increase from 2000 to 2021 : ' + str(total_increase_2000_2021))

fraction_total_energy_hydro = total_power_consumption(data, 2021, 'Hydro') / total_power_consumption_year(data, 2021)
print('The fraction of hydro energy to total power : ' + str(fraction_total_energy_hydro))

change_hydro_2000_2021 = total_power_consumption(data, 2021, 'Hydro') - total_power_consumption(data, 2000, 'Hydro')
print('The change in hydro energy from 2000 to 2021 : ' + str(change_hydro_2000_2021))

fraction_two_world_energy = ((total_power_consumption(data,2001,'Solar')+total_power_consumption(data,2001,'Wind'))/total_power_consumption_year(data,2001))-((total_power_consumption(data, 2000, 'Solar') + total_power_consumption(data, 2000, 'Wind')) / total_power_consumption_year(data, 2000))
print('The fraction of the world energy that is solar and wind in 2001 minus the fraction in 2000 : ' + str(fraction_two_world_energy))