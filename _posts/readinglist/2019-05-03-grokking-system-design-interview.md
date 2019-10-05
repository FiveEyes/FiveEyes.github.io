---
layout: post
title: "Grokking the System Design Interview"
date: 2019-05-03 04:40:00
categories: Tech
tags: [secret, reading]
---

# Grokking the System Design Interview

[Course home page](https://www.educative.io/collection/5668639101419520/5649050225344512)

## System Design Problems
  - [x] System Design Interviews: A step by step guide
  - [x] Designing a URL Shortening service like TinyURL
    - Let's design a URL shortening service like TinyURL. This service will provide short aliases redirecting to long URLs.
    - Similar services: bit.ly, goo.gl, qlink.me, etc.
    - Difficulty Level: Easy
    - KGS, Data Partition, Cache, Load Balance
  - [x] Designing Pastebin
    - Let's design a Pastebin like web service, where users can store plain text. Users of the service will enter a piece of text and get a randomly generated URL to access it. 
    - Similar Services: pastebin.com, pasted.co, chopapp.com 
    - Difficulty Level: Easy
    - Metadata database and Object storage
  - [ ] Designing Instagram
    - Let's design a photo-sharing service like Instagram, where users can upload photos to share them with other users.
    - Similar Services: Flickr, Picasa
    - Difficulty Level: Medium
  - [ ] Designing Dropbox
  - [ ] Designing Facebook Messenger
  - [ ] Designing Twitter
  - [ ] Designing Youtube or Netflix
  - [ ] Designing Typeahead Suggestion
  - [ ] Designing an API Rate Limiter
  - [ ] Designing Twitter Search
  - [ ] Designing a Web Crawler
  - [ ] Designing Facebook’s Newsfeed
  - [ ] Designing Yelp or Nearby Friends
  - [ ] Designing Uber backend
  - [ ] Design Ticketmaster (*New*)
  - [ ] Additional Resources

## System Design Basics
  - [ ] Key Characteristics of Distributed Systems
  - [ ] Load Balancing
  - [ ] Caching
  - [ ] Sharding or Data Partitioning
  - [ ] Indexes
  - [ ] Proxies
  - [ ] Redundancy and Replication
  - [ ] SQL vs. NoSQL
  - [ ] CAP Theorem
  - [ ] Consistent Hashing
  - [ ] Long-Polling vs WebSockets vs Server-Sent Events

## SQL vs. NoSQL

The most common types of NoSQL:
  * Key-Value Stores: Redis
  * Document Databases: MongoDB
  * Wide-Column Databases: HBase
  * Graph Databases

High level differences between SQL and NoSQL:
  * Storage
  * Schema
  * Querying
  * Scalability
  * Reliability or ACID Compliancy (Atomicity, Consistency, Isolation, Durability)

Reasons to use SQL database:
  * ensure ACID compliance.
  * data is structured and unchanging.

Reasons to use NoSQL database:
  * data is no structured
  * cloud computing
  * repid development

## Consistent Hashing



