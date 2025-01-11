<template>
    <div class="app">
        <Person :list="persons" />
    </div>
</template>

<script lang="ts" setup>
import Person from './components/Person.vue'
import { reactive } from 'vue'
import { type Persons } from '@/types'

let persons = reactive<Persons>([
    { id: "1", name: 'zhangsan', age: 18 },
    { id: "2", name: 'lisi', age: 20 },
    { id: "3", name: 'wangwu', age: 22 },
])

</script>

<style scoped></style>
