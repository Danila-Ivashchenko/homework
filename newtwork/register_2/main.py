from threading import Thread
import json
import requests
import whois
from datetime import date

def install_registry():
    print("Скачивание реестра")
    resp = requests.get("https://reestr.rublacklist.net/api/v3/snapshot/")
    data_list = resp.json()

    with open("data.json", "w+") as j_file:
        j_file.write(json.dumps(data_list, indent=4))
    j_file.close()

def get_register_data():
    try:
        with open("blocklist.json") as j_file:
            register_data = json.load(j_file)
        # date_in_data = list(register_data.keys())[0]
        # print(date_in_data, date.today())
        # if date_in_data != date.today():
        #     print("Обновление реестра")
        #     install_registry()
        #     get_register_data()
    except:
        install_registry()

    return register_data

def get_domains_with_https():
    print("Чтение реестра")
    data = get_register_data()
    https_domains = []
    for record in data:
        for current_record in data[record]:
            for url in current_record['urls']:
                if "https" in url:
                    https_domains += [current_record['domains'][0]]
    return list(set(https_domains))

def find_aviable_domains(domains):
    with open("aviable_domains.txt", "w+") as file:
        file.write("Домены на покупку")
    file.close()
    for domain in domains:
        try:
            if whois.whois(domain).status is None:
                print(domain)
                with open("aviable_domains.txt", "a") as file:
                    file.write(domain + "\n")
                file.close()
        except:
            continue

domains = get_domains_with_https()
n = 12

print("Обработка доменов")
for i in range(n):
    split_unique_domains = domains[(i * len(domains) // n):((i + 1) * len(domains) // n)]
    th = Thread(target=find_aviable_domains, args=(split_unique_domains,))
    th.start()

