import whois
import json
import requests
from threading import Thread
from datetime import date


def refresh_registry():
    print("----- refreshing registry -----")
    resp = requests.get("https://reestr.rublacklist.net/api/v3/snapshot/")
    blocklist = resp.json()

    with open("blocklist.json", "w+") as json_file:
        json_file.write(json.dumps(blocklist, indent=4))
    json_file.close()


def check_registry_freshness(block_list):
    try:
        today_date = date.today()
        test = block_list[str(today_date)]
        print(test)
    except:
        refresh_registry()


def get_black_list():
    try:
        with open("blocklist.json") as json_file:
            black_list = json.load(json_file)
        json_file.close()
    except:
        refresh_registry()

    check_registry_freshness(black_list)
    return black_list


def get_unique_domains_with_https():
    RKN_black_list = get_black_list()
    domains_with_https = []
    for date in RKN_black_list:
        for record in RKN_black_list[date]:
            for url in record['urls']:
                if "https" in url:
                    domains_with_https += [record['domains'][0]]
    return list(set(domains_with_https))


def additional_recording(record):
    with open("ready_to_register_domains.txt", "a") as file:
        file.write(record)
    file.close()


def get_split_array(arr, begin, end):
    return [arr[i] for i in range(begin, end)]


def find_aviable_domains(domain_list):
    with open("ready_to_register_domains_2.txt", "w+") as file:
        file.write("Свободные домены\n")
    file.close()
    for domain in domain_list:
        try:
            if whois.whois(domain).status is None:
                print(domain)
                additional_recording(domain + '\n')
        except:
            continue


if __name__ == '__main__':
    unique_domains = get_unique_domains_with_https()
    # количество потоков, а также частей массива
    n = 12
    print(len(unique_domains))
    print(n)
    for i in range(n):
        # передаём в функцию часть массива
        print(i)
        split_unique_domains = get_split_array(unique_domains, i * len(unique_domains) // n,
                                               (i + 1) * len(unique_domains) // n)
        th = Thread(target=find_aviable_domains, args=(split_unique_domains,))
        th.start()