import ipaddress
import json
from urllib.parse import urlparse

def parse_har_file(filename):
    '''Выгрузка информации из .har файла'''
    with open(filename, encoding="UTF-8") as file:
        data = json.load(file)
    return data

def get_ips():
    with open("ips.txt", "r") as file:
        ips = file.readlines()
    for i in range(len(ips)):
        if ips[i][-1] == '\n':
            ips[i] = ips[i][:-1]
    return ips

def get_domains_and_ids(filename):
    data = parse_har_file(filename)
    domains_and_ids = {}
    for record in data["log"]["entries"]:
        ip = record["serverIPAddress"]
        domain = urlparse(record["request"]["url"]).netloc
        if "https" in record["request"]["url"]:
            if domain in domains_and_ids:
                domains_and_ids[domain] += [ip]
            else:
                domains_and_ids[domain] = [ip]
    return domains_and_ids

def write_lists(list_1, list_2, list_3, title_1="", title_2="", title_3=""):
    with open("out.txt", "w+") as file:
        file.write(title_1 + "\n")
        for line in list_1:
            file.write("\t" + f"{line[0]  : <50}" + line[1] + "\n")
        file.write(title_2 + "\n")
        for line in list_2:
            file.write("\t" + f"{line[0]  : <50}" + line[1] + "\n")
        file.write(title_3 + "\n")
        for line in list_3:
            file.write("\t" + f"{line[0]  : <50}" + line[1] + "\n")


def separate_domains(filename):
    domains = get_domains_and_ids(filename)
    ips_list = get_ips()
    no_ip_domains = []
    in_list_ip_domains = []
    not_in_list_ip_domains = []

    for domain in domains:
        ips = domains[domain]
        ips = list(set(ips))
        for ip in ips:
            if ip == "":
                ips.remove(ip)
        if len(ips) == 0:
            no_ip_domains += [(domain, "none")]
        else:
            for ip in ips:
                in_list = False
                for ip_list in ips_list:
                    try:
                        if ipaddress.ip_address(ip) in ipaddress.ip_network(ip_list):
                            in_list = True
                    except:
                        continue
            if in_list:
                in_list_ip_domains += [(domain, ip)]
            else:
                not_in_list_ip_domains += [(domain, ip)]
    write_lists(no_ip_domains, in_list_ip_domains, not_in_list_ip_domains, "Domains without ips", "Domains with ips in list", "Domains with ips no in list")


filename = "m.vk.com.har"
separate_domains(filename)
